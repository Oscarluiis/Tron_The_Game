uniform vec2 frag_LightOrigin;
uniform vec3 frag_LightColor;
uniform float frag_LightAttenuation;
uniform vec2 frag_ScreenResolution;
uniform sampler2D texture;
void main (){

	vec2 baseDistance = gl_FragCoord.xy;
	baseDistance.y = frag_ScreenResolution.y-baseDistance.y;
	float d = length(frag_LightOrigin - baseDistance);
	float a = 1.0/(frag_LightAttenuation * d);
	vec4 color = vec4(a,a,a,1.0) * vec4(frag_LightColor, 1.0);
	vec4 te = texture2D(texture, gl_TexCoord[0].xy);

	if (text[0]>color[0]) color [0] = te [0];
	if (text[1]>color[1]) color [1] = te [1];
	if (text[2]>color[2]) color [2] = te [2];

	gl_FragColor=color;
}
