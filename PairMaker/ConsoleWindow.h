

// --- クラスの宣言
class ConsoleWindow
{
	// --- 公開変数とメンバ関数
	public:
		ConsoleWindow( );	// --- コンストラクタ
		~ConsoleWindow( );	// --- デストラクタ

	private:
		FILE *m_fIn;
		FILE *m_fOut;
};
