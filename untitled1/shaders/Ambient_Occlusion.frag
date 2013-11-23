const vec3 g_vec3AmbientResult = vec3(0.2, 0.2, 0.2); 
const vec3 g_vec3DiffuseResult = vec3(0.64, 0.64, 0.64); 
const vec3 g_vec3SpecularResult = vec3(1.0, 1.0, 1.0); 
const float g_fShininess = 100.0;

uniform vec3 g_vec3CameraPositinInModel; // 模型空间照相机位置 
uniform vec3 g_vec3LightPositionInModel; // 模型空间光源位置

uniform sampler2D g_AmbientOcclusion;

uniform bool g_bUseAmbientGene; // 是否使用Ambient Occlusion的标志

varying vec2 g_vec2TexCoord0; 
varying vec3 g_vec3Normal; 
varying vec3 g_vec3Vertex;

void main() 
{ 
 // 采样Ambient Occlusion因子 
 float fAmbientGene = texture2D(g_AmbientOcclusion, g_vec2TexCoord0).r;

 // 计算散射因子 
 vec3 L = normalize(g_vec3LightPositionInModel - g_vec3Vertex); 
 vec3 N = normalize(g_vec3Normal); 
 float fDiffuseGene = max(dot(N, L), 0.0);

 // 计算镜面光因子 
 float fSpecularGene = 0.0; 
 if (fDiffuseGene > 0.0) 
 { 
  vec3 V = normalize(g_vec3CameraPositinInModel - g_vec3Vertex); 
  vec3 H = normalize(L + V); 
  fSpecularGene = pow(max(dot(N, H), 0.0), g_fShininess); 
 }

 // 计算最终颜色      
 if (g_bUseAmbientGene) 
 { 
  // Ambient Occlusion只影响环境和散射选项 
  gl_FragColor = vec4(fAmbientGene*(g_vec3AmbientResult +  
      fDiffuseGene*g_vec3DiffuseResult) + 
      fSpecularGene*g_vec3SpecularResult, 
      1.0); 
 } 
 else 
 { 
  gl_FragColor = vec4(g_vec3AmbientResult +  
      fDiffuseGene*g_vec3DiffuseResult + 
      fSpecularGene*g_vec3SpecularResult, 
      1.0); 
 } 
}