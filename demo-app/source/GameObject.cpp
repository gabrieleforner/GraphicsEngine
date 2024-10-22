#include <GameObject.h>

GameObject GameObject::New_GameObject(string _name, Mesh _mesh) {
	GameObject gameObject;

	gameObject.name = _name;
	gameObject.mesh = _mesh;

	gameObject.transform.position = { 0,0,0 };
	gameObject.transform.rotation = { 0,0,0 };
	gameObject.transform.scale = { 1,1,1 };

	return gameObject;
}

void GameObject::Translate(glm::vec3 translation) {
	transform.position = translation;
}

void GameObject::Rotate(glm::vec3 _rotation) {
	transform.rotation = _rotation;
}

void GameObject::Rescale(glm::vec3 _scale) {
	transform.scale = _scale;
}