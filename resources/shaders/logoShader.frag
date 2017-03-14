uniform sampler2D texture;
uniform float currentTime;
uniform float duration;

void main()
{
	
	float percentTime = currentTime/duration;
	float fadeInPercent = currentTime/(duration*0.5);
	float fadeOutPercent = 1 - (currentTime - duration*0.7)/(duration*0.3);
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel.a = 0.f;
	if(percentTime <= 0.5)
	{
		pixel.a = fadeInPercent;
	}
	else if(percentTime <= 0.7)
	{
		pixel.a = 1.f;
	}
	else if(percentTime > 0.7)
	{
		pixel.a = fadeOutPercent;
	}
    gl_FragColor = gl_Color * pixel;
}