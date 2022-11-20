#include "Model.h"

#include "engine/src/graphics/bindable/VertexShader.h"
#include "engine/src/graphics/bindable/PixelShader.h"
#include "engine/src/graphics/bindable/PrimitiveTopology.h"

namespace engine::graphics::entity {
	Model::Model(const Graphics& gfx, const std::string& modelFilepath, const Texture& texture)
		: Entity<Model>(gfx, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f })
	{
		if (!IsStaticInitialized()) {
			AddStaticBind(std::make_unique<VertexShader>(gfx,
				L"sandbox\\res\\shaders\\ModelVS.hlsl",
				std::vector<engine::graphics::VertexShader::InputLayoutAttribute>
				{
					graphics::VertexShader::InputLayoutAttribute::POSITION,
					graphics::VertexShader::InputLayoutAttribute::TEXTURE,
					graphics::VertexShader::InputLayoutAttribute::NORMAL
				})
			);
			AddStaticBind(std::make_unique<PixelShader>(gfx,
				L"sandbox\\res\\shaders\\ModelPS.hlsl")
			);

			AddStaticBind(std::make_unique<PrimitiveTopology>(gfx, engine::graphics::PrimitiveTopology::Type::TRIANGLES));
		}

		AddBind(std::make_unique<Texture>(texture));
		AddBind(std::make_unique<TransformConstantBuffer>(gfx, *this));

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		LoadModel(modelFilepath);
		for (const auto& mesh : m_Meshes) {
			AddBind(std::make_unique<engine::graphics::Mesh>(mesh));
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	void Model::Draw() const noexcept
	{
		for (const auto& bind : GetStaticBinds()) {
			bind->Bind();
		}

		for (const auto& mesh : GetBinds()) {
			mesh->Bind();
		}

		for (const auto& mesh : GetBinds()) {
			if (const auto p = dynamic_cast<Mesh*>(mesh.get())) {
				mesh->Bind();
				m_Graphics->DrawIndexed(p->GetIndexBuffer().GetIndexCount());
			}
		}
	}

	void Model::SetOwnVertexShader(const std::wstring& filepath)
	{
		for (auto& vertexShader : GetBinds()) {
			if (dynamic_cast<graphics::VertexShader*>(vertexShader.get())) {
				vertexShader = std::make_unique<graphics::VertexShader>(*m_Graphics, filepath);
				return;
			}
		}

		AddBind(std::make_unique<graphics::VertexShader>(*m_Graphics, filepath));
	}

	void Model::SetOwnPixelShader(const std::wstring& filepath)
	{
		for (auto& pixelShader : GetBinds()) {
			if (dynamic_cast<graphics::PixelShader*>(pixelShader.get())) {
				pixelShader = std::make_unique<graphics::PixelShader>(*m_Graphics, filepath);
				return;
			}
		}

		AddBind(std::make_unique<graphics::PixelShader>(*m_Graphics, filepath));
	}
	

	void Model::LoadModel(const std::string& filepath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		if (pScene == nullptr) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, ("Can't open the model!\n" + filepath).c_str());
		}

		this->ProcessNode(pScene->mRootNode, pScene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->m_Meshes.push_back(this->ProcessMesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; ++i) {
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

	engine::graphics::Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
			Vertex vertex;

			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			if (mesh->mTextureCoords[0]) {
				vertex.Texture.x = (float)mesh->mTextureCoords[0][i].x;
				vertex.Texture.y = (float)mesh->mTextureCoords[0][i].y;
			}

			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;

			vertices.push_back(vertex);
		}


		for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
			aiFace face = mesh->mFaces[i];

			for (uint32_t j = 0; j < face.mNumIndices; ++j) {
				indices.push_back(face.mIndices[j]);
			}
		}

		return engine::graphics::Mesh(*m_Graphics, vertices, indices);
	}
}