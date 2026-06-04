#version 330 core
out vec4 FragColor;

in vec4 mColor;
in vec2 mTex;
in vec3 mNormal;

uniform bool useTexture;
uniform sampler2D tex;

void main()
{
    // if (useTexture) {
    FragColor = texture(tex, mTex);
    // FragColor = mColor;
    // } else {
    //     FragColor = mColor;
    // }
}
