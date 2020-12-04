#include "ofApp.h"

//--------------------------------------------------------------
void buildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos) {
	float verts[] = {
		-w + pos.x, -h + pos.y, pos.z,
		-w + pos.x, h + pos.y, pos.z,
		w + pos.x, h + pos.y, pos.z,
		w + pos.x, -h + pos.y, pos.z
	};

	float uvs[] = { 0,0, 0,1, 1,1, 1,0 };

	for (int i = 0; i < 4; i++) {
		int idx = i * 3;
		int uvIdx = i * 2;

		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvIdx], uvs[uvIdx + 1]));
	}

	ofIndexType indices[6] = { 0, 1, 2, 2, 3, 0 };
	mesh.addIndices(indices, 6);
}

//--------------------------------------------------------------
glm::mat4 buildMatrix(glm::vec3 trans, float rot, glm::vec3 scale) {
	using glm::mat4;
	glm::mat4 translation = glm::translate(trans);
	glm::mat4 rotation = glm::rotate(rot, vec3(0.0, 0.0, 1.0));
	glm::mat4 scaler = glm::scale(scale);
	return translation * rotation * scaler;
}

//--------------------------------------------------------------
void ofApp::buildPreset(int n) {
	switch (n) {
	case 0:

		break;
	case 1:
		modelArray[0][0] = buildMatrix(vec3(0.0, 0.0, 0.0), 0.0, vec3(1.0, 1.0, 1.0));

		modelArray[1][0] = buildMatrix(vec3(0.0, 0.5, 0.0), 0.0, vec3(1.0, 0.5, 1.0));
		modelArray[1][1] = buildMatrix(vec3(0.0, -0.5, 0.0), 0.0, vec3(1.0, 0.5, 1.0));

		modelArray[2][0] = buildMatrix(vec3(-0.5, 0.5, 0.0), 0.0, vec3(0.5, 0.5, 1.0));
		modelArray[2][1] = buildMatrix(vec3(0.5, 0.5, 0.0), 0.0, vec3(0.5, 0.5, 1.0));
		modelArray[2][2] = buildMatrix(vec3(-0.5, -0.5, 0.0), 0.0, vec3(0.5, 0.5, 1.0));
		modelArray[2][3] = buildMatrix(vec3(0.5, -0.5, 0.0), 0.0, vec3(0.5, 0.5, 1.0));

		modelArray[3][0] = buildMatrix(vec3(-0.5, 0.75, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][1] = buildMatrix(vec3(0.5, 0.75, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][2] = buildMatrix(vec3(-0.5, 0.25, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][3] = buildMatrix(vec3(0.5, 0.25, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][4] = buildMatrix(vec3(-0.5, -0.25, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][5] = buildMatrix(vec3(0.5, -0.25, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][6] = buildMatrix(vec3(-0.5, -0.75, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		modelArray[3][7] = buildMatrix(vec3(0.5, -0.75, 0.0), 0.0, vec3(0.5, 0.25, 1.0));
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	}
}

//--------------------------------------------------------------
bool ofApp::Collide(float wA, float hA, glm::vec3 posA, float wB, float hB, glm::vec3 posB) {
	if ((abs(posA.x - posB.x) < (wA + wB) * hardness) &&
		(abs(posA.y - posB.y) < (hA + hB) * hardness))
		return true;
	else
		return false;
}

//--------------------------------------------------------------
void ofApp::reset() {
	for (int i = 0; i < 8; i++) {
		charMesh[i].clear();
		obstacleMesh[i].clear();
	}
	backgroundMesh.clear();

	for (int i = 0; i < 4; i++)
		delete modelArray[i];
	delete[] modelArray;
	setup();
}

//--------------------------------------------------------------
void ofApp::setup(){
	stage = 1;
	srand(time(NULL));
	modelArray = new mat4*[4];
	for (int i = 0; i < 4; i++)
		modelArray[i] = new mat4[pow(2, i)];
	buildPreset(1);
	fixedFrameRate = ofGetFrameRate() / 3;
	std::cout << fixedFrameRate << endl;
	tmpHeight = new float*[8];
	for (int i = 0; i < 8; i++)
		tmpHeight[i] = new float[fixedFrameRate];

	hardness = 0.8f;
	gameStart = false;
	gameOver = false;
	jumpSpeed = 3.0f;
	fill_n(jumping, 8, false);
	fill_n(canJump, 8, true);
	fill_n(frameNum, 8, 0);
	characterInitialPosition = vec3(-0.7, -0.25, 0.0);
	score = 0.0f;
	frame = 0.0f;
	for (int i = 0; i < 8; i++) {
		charJumpPos[i] = vec3(0.0, 0.0, 0.0);
		obstacleMove[i] = 0.0f;
		obstacleInitialPosition[i] = vec3((float)(rand() % 3 + 1), -0.32, 0.0);
		for (int j = 0; j < fixedFrameRate; j++)
			tmpHeight[i][j] = 0.0f;
	}
	ofSetColor(0, 0, 0);

	ofDisableArbTex();

	for (int i = 0; i < 8; i++) {
		buildMesh(charMesh[i], 0.1, 0.2, characterInitialPosition);
		buildMesh(obstacleMesh[i], 0.1, 0.15, obstacleInitialPosition[i]);
	}
	buildMesh(backgroundMesh, 1.0, 1.0, vec3(0.0, 0.0, 0.5));
	buildMesh(gamestartTextMesh, 0.5, 0.2, vec3(0.0, 0.0, 0.0));
	buildMesh(gameoverTextMesh, 0.3, 0.2, vec3(0.0, 0.3, 0.0));
	buildMesh(restartTextMesh, 0.5, 0.2, vec3(0.0, -0.3, 0.0));
	buildMesh(jumpNoticeMesh, 0.5, 0.1, vec3(0.45, -0.85, 0.0));
	buildMesh(windowMesh, 1.0, 1.0, vec3(0.0, 0.0, 0.0));

	alienImg.load("walk_sheet.png");
	backgroundImg.load("forest.png");
	backgroundImg.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	obstacleImg.load("obstacle.png");
	gameoverTextImg.load("gameoverText.png");
	restartTextImg.load("restartText.png");
	gamestartTextImg.load("gamestartText.png");

	jumpNoticeImg[0].load("Notice1.png");
	jumpNoticeImg[1].load("Notice2.png");
	jumpNoticeImg[2].load("Notice3.png");
	jumpNoticeImg[3].load("Notice4.png");
	jumpNoticeImg[4].load("Notice5.png");
	jumpNoticeImg[5].load("Notice6.png");
	jumpNoticeImg[6].load("Notice7.png");
	jumpNoticeImg[7].load("Notice8.png");

	windowImg[0].load("Stage2.png");
	windowImg[1].load("Stage3.png");
	windowImg[2].load("Stage4.png");

	alphaTestShader.load("passthrough.vert", "alphaTest.frag");
	repeatingShader.load("repeatingBG.vert", "alphaTest.frag");
	obstacleShader.load("obstacle.vert", "alphaTest.frag");
	spritesheetShader.load("spritesheet.vert", "alphaTest.frag");
	textShader.load("passthrough.vert", "alphaTest.frag");
	noticeShader.load("textModel.vert","alphaTest.frag");
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < pow(2, stage - 1); i++) {
		if (jumping[i] && frameNum[i] < fixedFrameRate) {
			//tmpHeight[i][frameNum[i]] = ofGetLastFrameTime() * jumpSpeed * (fixedFrameRate - frameNum[i]);
			tmpHeight[i][frameNum[i]] =
				ofGetLastFrameTime() * jumpSpeed * (1.0 - charJumpPos[i].y);
			charJumpPos[i] += vec3(0.0, tmpHeight[i][frameNum[i]], 0.0);
			frameNum[i]++;
		}
		else if (jumping[i] && frameNum[i] < fixedFrameRate * 2) {
			charJumpPos[i] -= vec3(0.0, tmpHeight[i][(fixedFrameRate * 2 - 1) - frameNum[i]], 0.0);
			frameNum[i]++;
		}
		else if (jumping[i]) {
			frameNum[i] = 0;
			jumping[i] = false;
			canJump[i] = true;
		}
	}

	if (stage < 4) {
		if (score >= scoreOffset[stage - 1]) {
			stage++;
			timer = 0.0f;
			for (int i = 0; i < pow(2, stage - 2); i++)
				obstacleMove[i] = 0.0f;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDisableBlendMode();
	ofEnableDepthTest();

	//
	if (gameOver) {
		textShader.begin();
		textShader.setUniformTexture("Texture", gameoverTextImg, 0);
		gameoverTextMesh.draw();

		textShader.setUniformTexture("Texture", restartTextImg, 1);
		restartTextMesh.draw();

		textShader.end();
		ofDrawBitmapString(to_string((int)score), 100, 100, 1.0);
	}
	else if (!gameStart) {
		textShader.begin();
		textShader.setUniformTexture("Texture", gamestartTextImg, 0);
		gamestartTextMesh.draw();

		textShader.end();
	}
	else {
		if (timer <= 3.0f * stage)
			timer += ofGetLastFrameTime();
		frame = (frame > 10) ? 0.0 : frame += 0.2;
		vec2 spriteSize = vec2(0.28, 0.19);
		vec2 spriteFrame = vec2((int)frame % 3, (int)frame / 3);
		backgroundMove += ofGetLastFrameTime();

		if (stage > 1) {
			alphaTestShader.begin();
			alphaTestShader.setUniformTexture("Texture", windowImg[stage - 2], 0);
			windowMesh.draw();

			alphaTestShader.end();
		}

		for (int i = 0; i < pow(2, stage - 1); i++) {
			if (Collide(0.1, 0.2, characterInitialPosition + charJumpPos[i],
						0.1, 0.1, obstacleInitialPosition[i] - vec3(obstacleMove[i], 0.0, 0.0))) {
				gameOver = true;
			}

			obstacleMove[i] += ofGetLastFrameTime();
			if (obstacleInitialPosition[i].x - obstacleMove[i] < obstacleResetOffset[i])
				obstacleMove[i] = 0.0f;

			//
			if (timer <= 3.0f * stage) {
				noticeShader.begin();
				noticeShader.setUniformTexture("Texture", jumpNoticeImg[i], 0);
				noticeShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);
				jumpNoticeMesh.draw();

				noticeShader.end();
			}

			//
			obstacleShader.begin();
			obstacleShader.setUniformTexture("Texture", obstacleImg, 0);
			obstacleShader.setUniform1f("translation", obstacleMove[i]);
			obstacleShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);
			obstacleMesh[i].draw();

			obstacleShader.end();

			//
			spritesheetShader.begin();
			spritesheetShader.setUniform2f("size", spriteSize);
			spritesheetShader.setUniform2f("offset", spriteFrame);
			spritesheetShader.setUniform3f("translation", charJumpPos[i]);
			spritesheetShader.setUniformTexture("Texture", alienImg, 0);
			repeatingShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);
			charMesh[i].draw();

			spritesheetShader.end();

			//
			repeatingShader.begin();
			repeatingShader.setUniform1f("offset", backgroundMove);
			repeatingShader.setUniformTexture("Texture", backgroundImg, 0);
			repeatingShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);
			backgroundMesh.draw();

			repeatingShader.end();
		}

		ofDrawBitmapString(to_string((int)score), 100, 100, 1.0);
		if ((int)score > scoreOffset[stage - 1] - 20 && stage < 4) {
			ofDrawBitmapString(" Next Stage coming soon....", 95, 70, 1.0);
		}
		score += 5.0f * stage * ofGetLastFrameTime();

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (!gameOver && key == '1' && canJump[0] == true && gameStart) {
		jumping[0] = true;
		canJump[0] = false;
	}
	if (!gameOver && key == '2' && canJump[1] == true && stage >= 2) {
		jumping[1] = true;
		canJump[1] = false;
	}
	if (!gameOver && key == '3' && canJump[2] == true && stage >= 3) {
		jumping[2] = true;
		canJump[2] = false;
	}
	if (!gameOver && key == '4' && canJump[3] == true && stage >= 3) {
		jumping[3] = true;
		canJump[3] = false;
	}
	if (!gameOver && key == '5' && canJump[4] == true && stage >= 4) {
		jumping[4] = true;
		canJump[4] = false;
	}
	if (!gameOver && key == '6' && canJump[5] == true && stage >= 4) {
		jumping[5] = true;
		canJump[5] = false;
	}
	if (!gameOver && key == '7' && canJump[6] == true && stage >= 4) {
		jumping[6] = true;
		canJump[6] = false;
	}
	if (!gameOver && key == '8' && canJump[7] == true && stage >= 4) {
		jumping[7] = true;
		canJump[7] = false;
	}

	if (gameOver && key == ' ') {
		gameOver = false;
		reset();
	}

	if (!gameStart && key == ' ') {
		gameStart = true;
	}
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
