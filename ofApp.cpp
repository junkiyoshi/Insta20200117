#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int x_span = 256;
	int y_span = 240;

	for (int x = x_span * 0.5; x <= ofGetWidth(); x += x_span) {

		for (int y = y_span * 0.5; y <= ofGetWidth(); y += y_span) {

			for (int in = 10; in < 220; in += 30) {

				int color_index = ofRandom(this->color_list.size());
				ofColor color = this->color_list[color_index];

				int out = in + 15;
				int start_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, 100);
				int noise_value = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 1, 150);
				int end_param = start_param + noise_value;

				for (int param = start_param; param <= end_param; param++) {

					int index = this->mesh.getNumVertices();

					vector<glm::vec3> vertices;
					vertices.push_back(glm::vec3(x, y, 0) + glm::vec3(this->make_point(in, param), 0));
					vertices.push_back(glm::vec3(x, y, 0) + glm::vec3(this->make_point(out, param), 0));
					vertices.push_back(glm::vec3(x, y, 0) + glm::vec3(this->make_point(out, param + 1), 0));
					vertices.push_back(glm::vec3(x, y, 0) + glm::vec3(this->make_point(in, param + 1), 0));

					this->mesh.addVertices(vertices);

					for (int i = 0; i < vertices.size(); i++) {

						this->mesh.addColor(color);
					}

					this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
					this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 2); this->mesh.addIndex(index + 3);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.drawFaces();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}