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

in vec2 v_texCoord;

uniform sampler2D gSampler;

void main()
{
  frag_color = texture(gSampler, v_texCoord);
}
