/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <map>
#include <string>

#include "Common.hpp"
#include "rendering/MeshData.hpp"

class MeshFactory {
 public:
  static MeshFactory &GetInstance();

  std::shared_ptr<MeshData> LoadMesh(std::string path, std::string file,
                                     bool retain = false);
  void OnRelease(std::shared_ptr<MeshData> data);

 private:
  MeshFactory() {}
  MeshFactory(const MeshFactory &) = delete;
  MeshFactory &operator=(const MeshFactory &) = delete;

  std::map<std::string, std::shared_ptr<MeshData>> m_meshes;
  std::map<std::string, uint_t> m_refCount;
};
