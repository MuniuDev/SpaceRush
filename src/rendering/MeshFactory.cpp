/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/MeshFactory.hpp"
#include "rendering/MeshData.hpp"

MeshFactory &MeshFactory::GetInstance() {
  static MeshFactory instance;
  return instance;
}

std::shared_ptr<MeshData> MeshFactory::LoadMesh(std::string path,
                                                std::string file, bool retain) {
  std::string name = path + file;
  if (m_meshes.find(name) == m_meshes.end()) {
    LOGD("Assigning mesh memory: {}", name);
    auto meshData = std::make_shared<MeshData>(path, file);
    if (meshData->Init()) {
      m_meshes[name] = meshData;
      m_refCount[name] = (retain ? 2 : 1);
      return meshData;
    } else {
      LOGE("Failed to load mesh: {}", name);
      return std::shared_ptr<MeshData>();
    }
  } else {
    auto meshData = m_meshes[name];
    m_refCount[name] += 1;
    return meshData;
  }
}

void MeshFactory::OnRelease(std::shared_ptr<MeshData> data) {
  std::string name = data->GetName();
  m_refCount[name] -= 1;
  if (m_refCount[name] == 0) {
    LOGD("Freeing mesh memory: {}", name);
    m_meshes.erase(name);
  }
}
