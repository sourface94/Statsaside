#include <string>
#include "OpeningMenu.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Security;

[STAThread]//leave this as is
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FaceFinder::OpeningMenu form;
	Application::Run(%form);
}