#pragma once
#include "engine/src/graphics/drawable/Entity.h"
#include "engine/src/graphics/bindable/Mesh.h"


namespace engine::graphics::entity {
	class Model : public Entity<Model>
	{
	public:
		Model(const std::string& modelFilepath/*, const Texture& texture*/);

		void Draw() const noexcept override;

		void SetOwnVertexShader(const std::wstring& filepath);
		void SetOwnPixelShader(const std::wstring& filepath);

	private:
		void LoadModel(const std::string& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		engine::graphics::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<engine::graphics::Mesh> m_Meshes;
	};
}