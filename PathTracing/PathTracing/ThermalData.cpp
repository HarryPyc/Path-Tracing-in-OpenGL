#include "ThermalData.h"

float BBP(float T, int index) {
	float v = Wave[index];
	return 2e8 * (h * c * c * v * v * v) / (exp(100 * h * c * v / k / T) - 1);
}
void uploadThermalData(GLuint program, int index) {
	glUseProgram(program);
	const int n = 9;//total objects
	const float wall_refl = 1 - Emissivity[index][9], floor_refl = 1 - Emissivity[index][6], light_refl = 1 - Emissivity[index][3],
		sphere_refl = 1 - Emissivity[index][7], cone_refl = 1-Emissivity[index][4];
	float Reflectivity[n] = {
		wall_refl,wall_refl,wall_refl,wall_refl,wall_refl,floor_refl,
		light_refl,sphere_refl,cone_refl
	};
	glUniform1fv(glGetUniformLocation(program, "Reflectivity"), n, Reflectivity);
	float intensity[n];
	for (int i = 0; i < n; i++) {
		intensity[i] = BBP(Temprature[i]+273.15, index)*(1-Reflectivity[i]);
	}
	glUniform1fv(glGetUniformLocation(program, "Intensity"), n, intensity);
}

