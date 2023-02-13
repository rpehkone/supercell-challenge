uniform sampler2D texture;
uniform float iTime;

void main()
{
	vec2 uv = gl_TexCoord[0].xy;
	uv.y = -1.0 - uv.y;
	uv.x += sin(uv.y*10.0+iTime)/10.0;
	vec4 color = texture2D(texture, uv);
	gl_FragColor = color;
}
