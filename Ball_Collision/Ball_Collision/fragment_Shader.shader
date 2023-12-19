#version 330 core

uniform vec4 backgroundColor; // Specify the background color here

in
vec4 fragmentColor;
out
vec4 finalColor;

void main()
{
    // Use the background color as the default color
    finalColor = backgroundColor;

    // Add the color from the vertex shader
    finalColor += fragmentColor;
}