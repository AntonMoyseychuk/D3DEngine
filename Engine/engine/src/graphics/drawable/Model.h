#pragma once
#include "engine/src/graphics/drawable/Entity.h"
#include "engine/src/graphics/bindable/Texture.h"
#include "engine/src/graphics/bindable/TransformConstantBuffer.h"
#include "engine/src/graphics/bindable/Mesh.h"
#include "engine/src/window/Camera.h"


namespace engine::graphics::entity {
	class Model : public Entity<Model>
	{
	public:
		Model(const Graphics& gfx, const std::string& filepath, const Texture& texture);

		void Draw() const noexcept override;

	private:
		void LoadModel(const std::string& filepath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		engine::graphics::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<engine::graphics::Mesh> m_Meshes;
		engine::graphics::Texture m_Texture;
	};
}