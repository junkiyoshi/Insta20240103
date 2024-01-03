#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(255);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 1.44);

	string word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!";
	int sample_count = 180;
	auto noise_param = ofRandom(1000);

	for (int i = 0; i < word.size(); i++) {

		ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofNoFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);

				auto rotation_y = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				auto noise_value = ofNoise(location.x * 0.003, ofGetFrameNum() * 0.01);
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(noise_value, 0, 1, -180, 180) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				location = glm::vec4(location, 0) * rotation_x;

				ofVertex(location);
			}
		}
		ofEndShape(true);
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}