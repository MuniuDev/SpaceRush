/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#version 330 core

/* Structures */

struct BaseLight {
	vec3 color;
	float intensity;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

/* Params */

out vec4 frag_color;

in vec3 v_vertexPos;
in vec2 v_texCoord;
in vec3 v_normal;

uniform mat4 u_transform;

// lights
uniform BaseLight u_ambientLight;
uniform DirectionalLight u_directionalLight;

uniform sampler2D gSampler;

/* Functions */

// calculates ambient light
vec4 ambientlLight(BaseLight ambientLight) {
	if(ambientLight.intensity <= 0.0f) {
		return vec4(0.0f,0.0f,0.0f,0.0f);
	}

	return vec4(ambientLight.color * ambientLight.intensity, 1);
}

// calculates diffuse factor of any light
vec4 diffuseLight(BaseLight base, vec3 direction, vec3 normal) {
	if(base.intensity <= 0.0f)
		return vec4(0.0f,0.0f,0.0f,0.0f);

	vec4 diffuseColor = vec4(0.0f,0.0f,0.0f,0.0f);
	float diffuseFactor =  dot(normal,-direction);

	if(diffuseFactor > 0.0f ) {
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
	}

	return diffuseColor;
}

void main()
{
	// get texture color
	vec4 tex_color = texture(gSampler, v_texCoord);

	// transform position and normal to world coordinates
	vec3 normal = normalize(transpose(inverse(mat3(u_transform))) * v_normal);
	vec3 vertexPos = vec3(u_transform * vec4(v_vertexPos, 1));

	// ambient
	vec4 ambient = tex_color * ambientlLight(u_ambientLight);

	// directional (diffuse + specular)
	vec4 directional = tex_color * diffuseLight(u_directionalLight.base, u_directionalLight.direction, normal);

	// combine lights for final color
  frag_color = ambient + directional;
}
