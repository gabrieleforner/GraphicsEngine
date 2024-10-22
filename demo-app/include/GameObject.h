
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>

#include <string>

#define string std::string

#include <vector>


struct PushData {
    glm::mat4 transform{ 1.f };
};


struct Vertex {
	glm::vec3 position;
};


struct Mesh {
	//vertices contains the 3d coordinates to every vertex
	std::vector<Vertex> vertices;

	//triangles contains the combinations of vertices from which every triangle is made
	std::vector<glm::vec3> triangles;

};

struct Transform {
	glm::vec3 position = {};

	glm::vec3 rotation = {};

	glm::vec3 scale = { 1,1,1 };

    glm::mat4 mat4() {

        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        return glm::mat4{
            {
                scale.x * (c1 * c3 + s1 * s2 * s3),
                scale.x * (c2 * s3),
                scale.x * (c1 * s2 * s3 - c3 * s1),
                0.0f,
            },
            {
                scale.y * (c3 * s1 * s2 - c1 * s3),
                scale.y * (c2 * c3),
                scale.y * (c1 * c3 * s2 + s1 * s3),
                0.0f,
            },
            {
                scale.z * (c2 * s1),
                scale.z * (-s2),
                scale.z * (c1 * c2),
                0.0f,
            },
            {position.x, position.y, position.z, 1.0f} };
        }

};

class GameObject {
public:

	string name;
	Transform transform;
	Mesh mesh;

	GameObject New_GameObject(string name, Mesh mesh);

    void Translate(glm::vec3 _translation);
    void Rotate(glm::vec3 _rotation);
    void Rescale(glm::vec3 _scale);
};