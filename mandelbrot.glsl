uniform sampler1D tex;
uniform vec2 center;

varying vec4 pos;
void main() {

//float centerX = (pos.x - 1920.0 / 2.0)*4.0/1920.0;
//float centerY = (pos.y - 1080.0 / 2.0)*4.0 /1080.0;

float centerX = 1.333 * (gl_TexCoord[0].x - 0.5) * 0.6 - center.y;
float centerY = (gl_TexCoord[0].y - 0.5) * 0.6 - center.y;

float x = centerX;
float y = centerY;
int i;

for(i = 0; i < 700 ; i++)
{
	
	float nextX = (x*x - y*y) + centerX;
	float nextY = (x*y + x*y) + centerY;

	if( (nextX*nextX + nextY*nextY) > 4.0 ) break;
		
	x = nextX;
	y = nextY;
}
	gl_FragColor = texture1D(tex, (i == 700 ? 0.0 : float(i)) / 100.0);

	/*if( center.y == 0.7)
	{
		gl_FragColor = vec4(0.0,0.4,0.8,1.0);	
	}
	else 
	{
		gl_FragColor = vec4(0.8,0.2,0.0,1.0);
	}*/
	
}