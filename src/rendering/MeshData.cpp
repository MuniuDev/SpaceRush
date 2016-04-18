/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/MeshData.hpp"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

MeshData::MeshData(const std::string &path, const std::string &fileName)
    : m_path(path), m_fileName(fileName) {}

bool MeshData::Init() {
  m_meshEntries.clear();

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(m_path + m_fileName,
                                           aiProcessPreset_TargetRealtime_Fast);

  if (!scene) {
    LOGE("Error Importing Asset: {}", importer.GetErrorString());
    return false;
  }

  LOGD("Loading model {} sucessfull.", m_path + m_fileName);
  for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
    m_meshEntries.push_back(std::unique_ptr<MeshEntry>(
        new MeshEntry(m_path, scene->mMeshes[i], scene->mMaterials[i])));
  }
  return true;
}

void MeshData::Draw() {
  for (auto &meshEntry : m_meshEntries) {
    meshEntry->Draw();
  }
}
