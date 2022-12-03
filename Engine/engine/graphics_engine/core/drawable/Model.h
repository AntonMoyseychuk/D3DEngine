#pragma once
#include "engine/graphics_engine/core/drawable/GameObject.h"
#include "engine/graphics_engine/core/bindable/Mesh.h"

#include "engine/graphics_engine/core/bindable/Texture.h"


namespace graphics_engine::core::entity {
	class Model : public GameObject<Model>
	{
	public:
		Model(const std::string& modelFilepath, const Texture& texture);

		void Draw() const noexcept override;

		void SetOwnVertexShader(const std::wstring& filepath);
		void SetOwnPixelShader(const std::wstring& filepath);

	private:
		void LoadModel(const std::string& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		graphics_engine::core::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<graphics_engine::core::Mesh> m_Meshes;
	};
}