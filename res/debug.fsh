/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#version 330 core

/* Params */

out vec4 frag_color;

in vec3 v_vertexColor;

void main()
{
  frag_color = vec4(v_vertexColor,1);
}
