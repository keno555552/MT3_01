#include <Novice.h>
#include "myMath.h"
#include "imgui.h"

const char kWindowTitle[] = "GC01_05_カン_ケンリャン";

int kWindowWidth = 1280, kWindowHeight = 720;

///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
/// 重要定義、構造体作り
///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

enum stage { Title = 0, Stage, scoreBoard };
int stageHandle = Title;

// キー入力結果を受け取る箱
char keys[256] = { 0 };
char preKeys[256] = { 0 };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


	///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
	/// 初期化
	///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 cameraPosition{ 0.0f, 0.0f, -1.0f };

	Vector3 kLocalVertices[3] = { {0.0f, 0.1f, 0.0f}, // 頂部頂點
								  {-0.1f, -0.1f, 0.0f}, // 左下角頂點
								  {0.1f, -0.1f, 0.0f}  // 右下角頂點
								};

	Vector3 rotate{};

	Vector3 translate{};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
		/// ボタン処理
		///=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

		///=========================================================================================================================================================================================
		/// 更新処理
		///=========================================================================================================================================================================================

		// WSキーで前後に、ADキーで左右に三角形を動かす。伸縮回転をさせる。という処理をここに書く。translateとrotateの値を変更すれば良い。
		if (keys[DIK_W]) { translate.z += 0.1f; }
		if (keys[DIK_S]) { translate.z -= 0.1f; }
		if (keys[DIK_D]) { translate.x += 0.005f; }
		if (keys[DIK_A]) { translate.x -= 0.005f; }
		if (keys[DIK_Q]) { rotate.z += 0.01f; }
		if (keys[DIK_E]) { rotate.z -= 0.01f; }

		if (keys[DIK_R]) { translate = {}, rotate = {}; }

		rotate.y += 0.05f;

		// 各種行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		//Matrix4x4 projectionMatrix = MakeProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
		Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * (viewMatrix * perspectiveFovMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 screenVertices[3] = {};
		for (int i = 0; i < 3; ++i) {
			Vector3 ndcVertex = viewFinilTransform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = viewFinilTransform(ndcVertex, viewportMatrix);
		}


		///=========================================================================================================================================================================================
		/// 描画処理
		///=========================================================================================================================================================================================

		Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, BLACK, kFillModeSolid);

		VectorScreenPrintf(0, 0, cross, "Cross");

		// 描画
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		);

		VectorScreenPrintf(0, 20, screenVertices[0], "screenVertices[0]");
		MatrixScreenPrintf(0, 30, worldViewProjectionMatrix, "worldViewProjectionMatrix");
		Matrix4x4 viewMatrix2 = viewMatrix * perspectiveFovMatrix;
		MatrixScreenPrintf(0, 140, viewMatrix2);
		MatrixScreenPrintf(0, 250, viewportMatrix, "viewportMatrix");

		ImGui::Begin("rotate");
		ImGui::Text("rotateX");
		ImGui::SliderFloat("rotateX", &rotate.x, -3.14f, 3.14f);
		ImGui::Text("rotateY");
		ImGui::SliderFloat("rotateY", &rotate.y, -3.14f, 3.14f);
		ImGui::Text("rotateZ");
		ImGui::SliderFloat("rotateZ", &rotate.z, -3.14f, 3.14f);
		ImGui::End();

		ImGui::Begin("translate");
		ImGui::Text("translateX");
		ImGui::SliderFloat("translateX", &translate.x, -3.14f, 3.14f);
		ImGui::Text("translateY");
		ImGui::SliderFloat("translateY", &translate.y, -3.14f, 3.14f);
		ImGui::Text("translateZ");
		ImGui::SliderFloat("translateZ", &translate.z, -3.14f, 3.14f);
		ImGui::End();

		ImGui::Begin("cameraPosition");
		ImGui::Text("cameraPositionX");
		ImGui::SliderFloat("cameraPositionX", &cameraPosition.x, -3.14f, 3.14f);
		ImGui::Text("cameraPositionY");
		ImGui::SliderFloat("cameraPositionY", &cameraPosition.y, -3.14f, 3.14f);
		ImGui::Text("cameraPositionZ");
		ImGui::SliderFloat("cameraPositionZ", &cameraPosition.z, -3.14f, 3.14f);
		ImGui::End();

		ImGui::Begin("screenVertices");
		ImGui::Text("screenVerticesX");
		ImGui::SliderFloat("screenVerticesX", &screenVertices[0].x, -3.14f, 3.14f);
		ImGui::Text("screenVerticesY");
		ImGui::SliderFloat("screenVerticesY", &screenVertices[0].y, -3.14f, 3.14f);
		ImGui::Text("screenVerticesZ");
		ImGui::SliderFloat("screenVerticesZ", &screenVertices[0].z, -3.14f, 3.14f);
		ImGui::End();

		/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		/// StageEND
		/// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
