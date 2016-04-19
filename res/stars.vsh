/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#version 330 core

layout(location = 0) in vec3 a_vertexPos;

out vec2 vUv;

void main()
{
  vUv = a_vertexPos.xy;
  gl_Position = vec4(a_vertexPos, 1);
}
