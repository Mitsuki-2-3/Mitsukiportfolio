#include"DxLib.h"
#include"SceneManager.h"
#include"C3DTitle.h"
#include"FrameRateControll.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) 
{

    ChangeWindowMode(TRUE);
    SetGraphMode(1280, 720, 32);

    // ＤＸライブラリの初期化
    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    SetBackgroundColor(0x00, 0x00, 0x00);

    SetOutApplicationLogValidFlag(FALSE);               /*log*/
    SetMainWindowText("game");                    /*タイトル*/
    ChangeWindowMode(TRUE);                             /*窓表示*/
    SetUseDirect3DVersion(DX_DIRECT3D_11);              /*directX ver*/
    SetGraphMode(1280, 720, 32);                         /*解像度*/
    SetUseDirectInputFlag(TRUE);                        /*DirectInput使用*/
    SetDirectInputMouseMode(TRUE);                      /*DirectInputマウス使用*/
    SetWindowSizeChangeEnableFlag(TRUE, TRUE);        /*ウインドウサイズを手動変更不可、ウインドウサイズに合わせて拡大もしないようにする*/
    SetUsePixelLighting(TRUE);                          /*ピクセルライティングの使用*/
    SetFullSceneAntiAliasingMode(4, 2);                 /*アンチエイリアス*/
    SetWaitVSyncFlag(TRUE);                             /*垂直同期*/
    DxLib_Init();                                       /*ＤＸライブラリ初期化処理*/
    SetSysCommandOffFlag(TRUE);                         /*タスクスイッチを有効にするかどうかを設定する*/
    SetAlwaysRunFlag(TRUE);                             /*background*/
    SetUseZBuffer3D(TRUE);                              /*zbufuse*/
    SetWriteZBuffer3D(TRUE);                            /*zbufwrite*/

    //フレームレート用の変数準備
    FrameRateControll* frame;
    frame = new FrameRateControll();

    SceneManager sceneMng(dynamic_cast<AbstractScene*>(new C3DTitle()));

    while (ProcessMessage() == 0)   //メインの更新
    {
        ClearDrawScreen();		//画面初期化
        frame->Update();
        sceneMng.Update();		//シーン更新処理
        frame->Draw();
        sceneMng.Draw();		//シーン描画処理

        frame->Wait();
        if (sceneMng.ChangeScene() == nullptr)		//シーン変更処理
        {
            DxLib_End();		//DxLib終了
            return 0;			//ソフト終了
        }
        ScreenFlip();			//裏画面の内容を表画面に反映
    }


    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}