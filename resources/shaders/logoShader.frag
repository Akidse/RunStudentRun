uniform sampler2D texture;
uniform float percentTime;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel.a = percentTime;
    gl_FragColor = gl_Color * pixel;
	//gl_FragColor = vec4(0.5,0.5,0.5,1.);
}