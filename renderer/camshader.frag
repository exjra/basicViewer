#version 330

in vec2 TexCoord;

out vec4 colour;

uniform sampler2D theTexture;

void main()
{
//    colour = texture(theTexture, TexCoord);

    vec4 texColor = texture(theTexture, TexCoord);
//    if(texColor.a < 0.01)
//        discard;
    colour = vec4(texColor.r, texColor.g, texColor.b, texColor.w); //bgr convertion

    //emboss effect
    /*
    vec2 onePixel = vec2(1.0 / 480.0, 1.0 / 320.0);

    vec4 color;
    color.rgb = vec3(0.5);
    color -= texture2D(theTexture, TexCoord - onePixel) * 5.0;
    color += texture2D(theTexture, TexCoord + onePixel) * 5.0;

    color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    colour = vec4(color.rgb, 1);
    */
}
