# AlienJump-Multiply

#### 사용언어 및 툴 : C++, GLSL, openGL(v4.1), openframeworks(v0.10.0_vs2017_release)
#### 작업 인원 : 1인 프로젝트

-----------------------
![Intro](https://user-images.githubusercontent.com/75113789/101166611-ea9d8080-367b-11eb-8729-832c76d916e7.PNG)
> ###### 클라이언트를 실행하면 나타나는 초기화면
> ###### 스페이스바를 눌러 게임 시작

-----------------------
![Stage1](https://user-images.githubusercontent.com/75113789/101171663-71099080-3683-11eb-96a5-897738385702.PNG)
> ###### 스테이지 1 화면
> ###### 숫자키 1로 점프

-----------------------
![Stage2](https://user-images.githubusercontent.com/75113789/101171666-723abd80-3683-11eb-8e58-03c51d64abfc.PNG)
> ###### 스테이지 2 화면
> ###### 숫자키 1 ~ 2로 점프

-----------------------
![Stage3](https://user-images.githubusercontent.com/75113789/101171667-723abd80-3683-11eb-9e45-c9a00dbf384f.PNG)
> ###### 스테이지 3 화면
> ###### 숫자키 1 ~ 4로 점프

-----------------------
![Stage4](https://user-images.githubusercontent.com/75113789/101171668-72d35400-3683-11eb-95b6-9a9e6738817f.PNG)
> ###### 스테이지 4 화면
> ###### 숫자키 1 ~ 8로 점프

-----------------------
# < 작업 내용 >
###### * 클라이언트 코드 및 바인드 할 버텍스 셰이더, 프래그먼트 셰이더들을 C++, GLSL로 작성
###### * setup() : 게임에 사용될 메쉬 생성, 이미지 로드, 그리고 셰이더 바인딩, 변수 초기화
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
	
	alphaTestShader.load("passthrough.vert", "alphaTest.frag");
	repeatingShader.load("repeatingBG.vert", "alphaTest.frag");
	obstacleShader.load("obstacle.vert", "alphaTest.frag");
	spritesheetShader.load("spritesheet.vert", "alphaTest.frag");
	textShader.load("passthrough.vert", "alphaTest.frag");
	noticeShader.load("textModel.vert","alphaTest.frag");
	
###### * update() : 점프키(각 번호키)가 눌렸을 때 캐릭터 위치 계산, 점수에 따라 스테이지 변경
	for (int i = 0; i < pow(2, stage - 1); i++) {
		if (jumping[i] && frameNum[i] < fixedFrameRate) {
			tmpHeight[i][frameNum[i]] =	ofGetLastFrameTime() * jumpSpeed * (1.0 - charJumpPos[i].y);
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
	
###### * draw() : 실질적으로 메쉬들을 렌더링(셰이더에 필요한 유니폼 변수를 전달하고, 메쉬 드로우)
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
		
###### * buildPreset(..) : 스테이지에 따라 셰이더로 4차원 행렬값을 전달해 화면에 이미지가 렌더링 될 크기 및 위치를 변경
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
	...
		
	obstacleShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);
	repeatingShader.setUniformMatrix4f("model", modelArray[stage - 1][i]);

###### * Collide(..) : 충돌검사를 진행할 때 hardness 변수를 곱해 충돌검사 난이도 조절
	if ((abs(posA.x - posB.x) < (wA + wB) * hardness) && (abs(posA.y - posB.y) < (hA + hB) * hardness))
		return true;

###### * 버텍스 셰이더의 "offset", "translation" 변수로 이전 프레임으로부터 흐른 시간(ofGetLastFrameTIme())을 전달해 배경과 장애물이 일정하게 움직이게끔 함 	
	backgroundMove += ofGetLastFrameTime();
	...
	repeatingShader.setUniform1f("offset", backgroundMove);
	obstacleShader.setUniform1f("translation", obstacleMove[i]);
	...
	fragUV = vec2(uv.x, 1.0 - uv.y) + vec2(offset / 2, 0.0);

-----------------------
# < 실행 방법 >
#### bin\Multiply.exe 실행
