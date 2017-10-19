attribute vec3 vp;
attribute vec3 co;
attribute vec2 uv;

uniform mat4 MVP;

varying vec4 pos;
void main() {
pos = vec4(vp, 1.0) * MVP;
gl_Position = pos;
}