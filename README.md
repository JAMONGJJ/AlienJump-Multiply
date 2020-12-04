# AlienJump-Multiply

#### 사용언어 및 툴 : C++, GLSL, openGL(v4.1), openframeworks(v0.10.0_vs2017_release)
#### 작업 인원 : 1인 프로젝트

-----------------------
# < 작업 내용 >
###### 1. 클라이언트 코드 및 바인드 할 버텍스 셰이더, 프래그먼트 셰이더들을 C++, GLSL로 작성
###### 2. 스테이지가 하나씩 올라갈 때마다 렌더링되는 이미지들이 2배로 증가

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
###### 3. 스테이지에 따라 셰이더로 4차원 행렬값을 전달해 화면에 이미지가 렌더링 될 크기 및 위치를 변경

		if ((abs(posA.x - posB.x) < (wA + wB) * hardness) && (abs(posA.y - posB.y) < (hA + hB) * hardness))
			return true;
###### 4. 충돌검사를 진행할 때 hardness 변수를 곱해 충돌검사 난이도 조절
	
	backgroundMove += ofGetLastFrameTime();
	...
	repeatingShader.setUniform1f("offset", backgroundMove);
	obstacleShader.setUniform1f("translation", obstacleMove[i]);
	...
	fragUV = vec2(uv.x, 1.0 - uv.y) + vec2(offset / 2, 0.0);
###### 5. 버텍스 셰이더의 "offset", "translation" 변수로 이전 프레임으로부터 흐른 시간(ofGetLastFrameTIme())을 전달해 배경과 장애물이 일정하게 움직이게끔 함 

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

# < 실행 방법 >
#### bin\Multiply.exe 실행
