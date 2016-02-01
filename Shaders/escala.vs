
void main()
{	
   vec4 scaledPos = vec4(0.5*gl_Vertex.xy, 0.0, 1.0);
   gl_Position = gl_ModelViewProjectionMatrix * scaledPos;
}
