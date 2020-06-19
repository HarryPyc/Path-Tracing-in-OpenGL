#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_TRIANGLE_IN_LEAF = 64;

struct TreeNode {
	unsigned int axis; int firstTriangle = -1, triangleCount = 0; int isLeaf = 0;
	glm::vec3 minBb; int left = -1;
	glm::vec3 maxBb; int right = -1;
	int parent = -1; float val; int PADDING1, PADDING2;
	TreeNode(glm::vec3 _minBb, glm::vec3 _maxBb)
		: minBb(_minBb), maxBb(_maxBb) {};
};
struct Triangle {
	int index;
	glm::vec3 center;
	Triangle(int _index, glm::vec3 _center) :index(_index), center(_center) {};
};
typedef vector<Triangle>::iterator iter;
class KdTree {
public:
	vector<glm::vec4> Vertices;
	vector<glm::uvec4> Triangles;

	vector<TreeNode> nodeList;
	vector<Triangle> triangleList;

	void ConstructKdTree();
private:
	void helper(TreeNode &root, iter begin, iter end);
	void CalculateCenter();
};
