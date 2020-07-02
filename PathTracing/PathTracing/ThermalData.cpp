#include "ThermalData.h"

float BBP(float T, int index) {
	float v = Wave[index];
	double res = 2e8 * (h * c * c * v * v * v) / (exp(100 * h * c * v / k / T) - 1);
	return float(res);
}
void uploadThermalData(GLuint program, int index) {
	glUseProgram(program);
	const int n = 2;//total objects
	
	float Reflectivity[n] = {
		1-Emissivity[index][3], 1-Emissivity[index][0]
	};
	glUniform1fv(glGetUniformLocation(program, "Reflectivity"), n, &Reflectivity[0]);
	float intensity[n];
	for (int i = 0; i < n; i++) {
		intensity[i] = BBP(Temprature[i]+273.15, index)*(1-Reflectivity[i]);
	}
	glUniform1fv(glGetUniformLocation(program, "Intensity"), n, &intensity[0]);
	
}

