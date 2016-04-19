// Source: http://shaderfrog.com/app/view/273?view=shader
#version 330 core

out vec4 frag_color;

uniform float u_time;
uniform float u_starRadius;
uniform vec3 u_starColor;
uniform float u_starDensity;
uniform float u_speed;
uniform vec2 u_resolution;

in vec2 vUv;

float starrand(float seedx, float seedy, int seedp) {
    return 0.05 + 0.9 * fract(
        sin(float(seedp) * 437.234) * 374.2542 -
        cos(seedx * 432.252) * 23.643 +
        sin(seedy * 73.2454) * 372.23455
    );
}

void main() {

    vec2 position = vUv.xy * u_resolution.xy;

    frag_color = vec4(0.0, 0.0, 0.0, 1.0);

    for ( int p = 0; p < 20; p++ ) {
        float scale = ( 1.0 / u_starRadius ) + float( p );
        vec2 vpos = position * scale;
        vpos.y += u_speed * u_time / scale;
        vec2 spos = vec2(
            starrand(floor(vpos.x), floor(vpos.y), p),
            starrand(10.5 + floor(vpos.x), 10.5 + floor(vpos.y), p)
        );
        float px = scale / 80.0 / 3.0;
        float size = 1.0 / (scale * ( 500.0 / u_starDensity ) );
        float brite = 1.0;

        if( size < px ) {
            brite = size / px;
            size = px;
        }

        frag_color.rgb += u_starColor * min(
            1.0, max(0.0, u_starDensity - length(spos - fract(vpos)) / size)
        ) * brite;
    }

}
