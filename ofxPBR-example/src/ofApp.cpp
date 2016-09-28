#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(0);
	ofSetVerticalSync(false);

    ofDisableArbTex();
    
    cam.setupPerspective(false, 60, 1, 12000);
    
    cubeMap.load("Barce_Rooftop_C_3k.jpg", 1024, true, "filteredMapCache");
    pbr.setup(1024);
    pbr.setCubeMap(&cubeMap);
    
    render.load("ofxPBRShaders/default2.vert", "ofxPBRShaders/default2.frag");

    scene = bind(&ofApp::renderScene, this);
    
    light.setLightType(LightType_Directional);
    light.setPosition(-1500, 1000, 1500);
    light.lookAt(ofVec3f(0));
    light.setScale(1.5);
    light.setColor(ofFloatColor(1.0));
    light.setShadowType(ShadowType_Hard);
    pbr.addLight(&light);
    
    //light2.setLightType(LightType_Directional);
    //light2.setPosition(1500, 500, 1500);
    //light2.lookAt(ofVec3f(0));
    //light2.setScale(1.5);
    //light2.setColor(ofFloatColor(1.0));
    //light2.setShadowType(ShadowType_Hard);
    //pbr.addLight(&light2);

//	float offset = -PI / 2;
//	int numLights = 2;

//	lights[0].setLightType(LightType_Point);
//	lights[0].setPosition(-500 * sin(2 * PI * (offset + float(0) / numLights)), 100, 500 * cos(2 * PI * (offset + float(0) / numLights)));
//	lights[0].lookAt(ofVec3f(0));
//	lights[0].setScale(1.5);
//	lights[0].setColor(ofFloatColor(1, 0, 1, 1.0));
//	lights[0].setShadowType(ShadowType_Hard);
//	lights[0].setRadius(1000);
//	lights[0].setFarClip(5000);
//	pbr.addLight(&lights[0]);

//	for (int i = 0; i < numLights; i++) {
//		lights[i].setLightType(LightType_Point);
//		lights[i].setPosition(-250 * sin(2 * PI * (offset + float(i) / numLights)), 100, 250 * cos(2 * PI * (offset + float(i) / numLights)));
//		lights[i].lookAt(ofVec3f(0));
//		lights[i].setScale(1.5);
//		lights[i].setColor(ofFloatColor(1, 1, 1, 1.0));
//		lights[i].setShadowType(ShadowType_Hard);
//		lights[i].setRadius(5000);
//		lights[i].setFarClip(5000);
//		pbr.addLight(&lights[i]);
//	}
    
    cubeMap.setEnvLevel(0.3);
    
    cam.setNearClip(0.0);
    cam.setFarClip(10000);
    
    ofFbo fbo;
    fbo.begin();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	prevTime = ofGetElapsedTimef();
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
    pbr.makeDepthMap(scene);
    
	//glCullFace(GL_FRONT);
	cam.begin();
	pbr.drawEnvironment(&cam);
	scene();
	cam.end();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	prevTime = ofGetElapsedTimef() - prevTime;
	ofDrawBitmapString(ofToString(prevTime), 20, 20);
}

//--------------------------------------------------------------
void ofApp::renderScene(){
    ofEnableDepthTest();
    ofPushMatrix();
    pbr.begin(&cam, &render);
    {
        material.roughness = 0.0;
        material.metallic = 0.0;
        material.begin(&pbr);
        ofDrawBox(0, -40, 0, 2000, 10, 2000);
        material.end();
        
        ofSetColor(255,0,0);
        for(int i=0;i<10;i++){
            material.roughness = float(i) / 9.0;
            for(int j=0;j<10;j++){
                material.metallic = float(j) / 9.0;
                material.begin(&pbr);
                ofDrawSphere(i * 100 - 450, 0, j * 100 - 450, 35);
                material.end();
            }
        }
    }
    pbr.end();
    ofPopMatrix();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
