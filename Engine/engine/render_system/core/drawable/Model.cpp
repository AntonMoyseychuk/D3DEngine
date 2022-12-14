#include "Model.h"

#include "engine/render_system/core/bindable/VertexShader.h"
#include "engine/render_system/core/bindable/PixelShader.h"
#include "engine/render_system/core/bindable/PrimitiveTopology.h"

#include "engine/render_system/core/bindable/TransformConstantBuffer.h"

#include "engine/utility/parser/StringParser.h"


namespace engine::graphics::core {
	const std::vector<Mesh>& Model::GetMeshes() const noexcept
	{
		return m_Meshes;
	}
	
	Model::Model(const std::wstring& filepath/*, const Texture& texture*/)
		: Resource(filepath), GameObject<Model>({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f })
	{
		if (!IsStaticInitialized()) {
			AddStaticBind(std::make_unique<VertexShader>(L"sandbox\\res\\shaders\\ModelVS.hlsl",
				std::vector<graphics::core::VertexShader::InputLayoutAttribute> 
				{
					core::VertexShader::InputLayoutAttribute::POSITION,
					core::VertexShader::InputLayoutAttribute::TEXTURE,
					core::VertexShader::InputLayoutAttribute::NORMAL
				})
			);
			AddStaticBind(std::make_unique<core::PixelShader>(L"sandbox\\res\\shaders\\ModelPS.hlsl"));
			AddStaticBind(std::make_unique<core::PrimitiveTopology>(core::PrimitiveTopology::Type::TRIANGLES));
		}

		//AddBind(std::make_unique<Texture>(texture), GetBinds().end());
		AddBind(std::make_unique<core::TransformConstantBuffer>(*this), GetBinds().end());

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		LoadModel(util::StringParser::ToString(filepath));
		for (const auto& mesh : m_Meshes) {
			AddBind(std::make_unique<core::Mesh>(mesh), GetBinds().end());
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	//void Model::Draw() const noexcept
	//{
	//	for (const auto& bind : GetStaticBinds()) {
	//		bind->Bind();
	//	}
	//
	//	for (const auto& bindable : GetBinds()) {
	//		bindable->Bind();
	//		if (const auto mesh = dynamic_cast<Mesh*>(bindable.get())) {
	//			RenderSystem::Get().DrawIndexed(mesh->GetIndexBuffer().GetIndexCount());
	//		}
	//	}
	//}
	//
	//void Model::SetOwnVertexShader(const std::wstring& filepath)
	//{
	//	for (auto& vertexShader : GetBinds()) {
	//		if (dynamic_cast<core::VertexShader*>(vertexShader.get())) {
	//			vertexShader = std::make_unique<core::VertexShader>(filepath);
	//			return;
	//		}
	//	}
	//
	//	AddBind(std::make_unique<core::VertexShader>(filepath), GetBinds().begin());
	//}
	//
	//void Model::SetOwnPixelShader(const std::wstring& filepath)
	//{
	//	for (auto& pixelShader : GetBinds()) {
	//		if (dynamic_cast<core::PixelShader*>(pixelShader.get())) {
	//			pixelShader = std::make_unique<core::PixelShader>(filepath);
	//			return;
	//		}
	//	}
	//	AddBind(std::make_unique<core::PixelShader>(filepath), GetBinds().begin());
	//}

	void Model::LoadModel(const std::string& filepath)
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		THROW_EXCEPTION_IF_LOGIC_ERROR(pScene == nullptr, "MODEL", "Can't find the model.\nModel filepath: " + filepath);

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

	graphics::core::Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

		return graphics::core::Mesh(vertices, indices);
	}
}