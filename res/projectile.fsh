/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#version 330 core

out vec4 frag_color;

uniform vec3 u_color;

void main() {
  frag_color = vec4(u_color, 1);
}
