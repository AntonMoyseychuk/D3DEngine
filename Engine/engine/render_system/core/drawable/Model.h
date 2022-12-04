#pragma once
#include "engine/render_system/core/drawable/GameObject.h"
#include "engine/render_system/core/bindable/Mesh.h"

#include "engine/render_system/core/bindable/Texture.h"
#include "engine/render_system/core/resource_manager/Resource.h"


namespace engine::graphics::core {
	class Model : public GameObject<Model>, public Resource
	{
		friend class ModelManager;

	public:
		const std::vector<Mesh>& GetMeshes() const noexcept;

		//void Draw() const noexcept override;

		//void SetOwnVertexShader(const std::wstring& filepath);
		//void SetOwnPixelShader(const std::wstring& filepath);

	private:
		Model(const std::wstring& filepath/*, const Texture& texture*/);

		void LoadModel(const std::string& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		core::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<Mesh> m_Meshes;
	};
}