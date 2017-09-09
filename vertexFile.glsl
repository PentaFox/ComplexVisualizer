attribute vec3 vp;
attribute vec3 co;
uniform mat4 MVP;
varying vec3 color;
void main() {
color = co;
gl_Position = vec4(vp, 1.0) * MVP;
}