#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(1280, 847);
	bool loadingOk = imgSource.load("tgv.jpg");
	if (!loadingOk) {
		ofLogError() << "Image non trouvée";
	}
	imgResult.allocate(imgSource.getWidth(), imgSource.getHeight(),
		OF_IMAGE_COLOR);

	bool backgroundLoadingOk = background.load("fondvert.jpg");
	if (!backgroundLoadingOk) {
		ofLogError() << "Image non trouvée";
	}

}

//--------------------------------------------------------------
ofColor ofApp::filter(ofColor color, int effectP, float p) {
	float r = color.r;
	float g = color.g;
	float b = color.b;
	float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

	if (effectP == 1) {
		ofColor inversedColor = ofColor(255 - r, 255 - g, 255 - b);
		return inversedColor;
	} else if (effectP == 2) {
		float grey = (r + g + b) / 3;
		ofColor greyColor = ofColor(grey, grey, grey);
		return greyColor;
	} else if (effectP == 3) {
		ofColor greyColor = ofColor(luminance, luminance, luminance);
		return greyColor;
	}
	else if (effect == 4) {
		float k = (p - 0.5f) * 256;
		int newRed = ofClamp(r + k, 0, 255);
		int newGreen = ofClamp(g + k, 0, 255);
		int newBlue = ofClamp(b + k, 0, 255);
		ofColor brightnessColor = ofColor(newRed, newGreen, newBlue);
		return brightnessColor;
	}
	else if (effect == 5) {
		float k = p *  3;
		int newRed = ofClamp((r -128) * k + 128, 0, 255);
		int newGreen = ofClamp((g - 128) * k + 128, 0, 255);
		int newBlue = ofClamp((b - 128) * k + 128, 0, 255);
		ofColor saturationColor = ofColor(newRed, newGreen, newBlue);
		return saturationColor;
	}
	else if (effect == 6) {
		float SepiaR = ofClamp(r * 0.393 + g * 0.769 + b * 0.189, 0, 255);
		float SepiaG = ofClamp(r * 0.349 + g * 0.686 + b * 0.168, 0, 255);
		float SepiaB = ofClamp(r * 0.272 + g * 0.534 + b * 0.131, 0, 255);
		ofColor sepiaColor = ofColor(SepiaR, SepiaG, SepiaB);
		return sepiaColor;
	} else if (effect == 7) {

	}

	else {
		return color;
	}
}
//--------------------------------------------------------------
void ofApp::update() {
	/*
	int px = ofClamp(mouseX, 0, imgSource.getWidth() - 1);
	int py = ofClamp(mouseY, 0, imgSource.getHeight() - 1);
	currentColor = imgSource.getColor(px, py);
	*/


	float power = mouseX / (float)ofGetWidth();

	for (int y = 0; y < imgSource.getHeight(); y++) {
		for (int x = 0; x < imgSource.getWidth(); x++) {
			ofColor transferColor = imgSource.getColor(x, y);
			ofColor modifiedColor = filter(transferColor, effect, power);
			imgResult.setColor(x, y, modifiedColor);
		}
	}
	imgResult.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255);
	imgSource.draw(0, 0);
	imgResult.draw(0, 0);

	//ofSetColor(currentColor);
	//ofDrawRectangle(mouseX + 10, mouseY + 10, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_RIGHT) {
		effect++;
	}
	if (key == OF_KEY_LEFT) {
		effect--;
	}
	effect = (effect + numberEffect) % numberEffect;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
