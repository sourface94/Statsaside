#pragma once
#include <algorithm> //for std::transform 
#include <functional> 
#include <cctype>
#include <locale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <msclr/marshal_cppstd.h>
#include "GlobalVariables.h"
#include "FacialComputations.h"
#include "FileComputations.h"

namespace FaceFinder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Windows::Forms;
	using namespace std;

	/// <summary>
	/// Summary for OpeningMenu
	/// </summary>
	public ref class OpeningMenu : public System::Windows::Forms::Form
	{

	public:
		OpeningMenu(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OpeningMenu()
		{
			if (components) {
				delete components;
			}

			FileComputations::deleteFiles(FileComputations::getImagesFilesFromHome());
		}

	protected:



	private: System::Windows::Forms::TextBox^  saveTextBox;

	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  openMenutab;




	private: System::Windows::Forms::TabPage^  saveProfileTab;
	private: System::Windows::Forms::TabPage^  searchResultstab;

	private: System::Windows::Forms::TabPage^  searchFoldertab;
	private: System::Windows::Forms::Button^  chooseFolderbtn;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::TextBox^  folderTextbox;
	private: System::Windows::Forms::Button^  backToOpen;

	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Button^  btnMoveS;
	private: System::Windows::Forms::Button^  btnDeleteS;

	private: System::Windows::Forms::ListView^  resultsListView;
	private: System::Windows::Forms::Button^  backToNewProf;

	private: System::Windows::Forms::ImageList^  resultsImagelist;
	private: System::Windows::Forms::ImageList^  profilesImageList;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private: System::Windows::Forms::Button^  viewResultsbtn;
	private: System::Windows::Forms::Button^  toChoosefolderbtn;
	private: System::Windows::Forms::RadioButton^  selectRadioBtn;
	private: System::Windows::Forms::RadioButton^  unselectRadioBtn;
	private: System::Windows::Forms::Label^  noResultsLabel;
	private: System::Windows::Forms::Button^  chooseProfilebtn;
	private: System::Windows::Forms::ListView^  profilesListView;

	private: System::Windows::Forms::TextBox^  subjectTextBox;
	private: System::Windows::Forms::Button^  selectFilesButton;
	private: System::Windows::Forms::Button^  openFilesButton;


	private: System::Windows::Forms::Label^  previousProfileLabel;
	private: System::Windows::Forms::Button^  resultsFinishBtn;
	private: System::Windows::Forms::Button^  resultsBackBtn;
	private: System::Windows::Forms::TextBox^  folderTextbox3;

	private: System::Windows::Forms::Button^  chooseFolderBtn3;
	private: System::Windows::Forms::TextBox^  folderTextbox2;

	private: System::Windows::Forms::Button^  chooseFolderBtn2;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog2;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog3;
	private: System::Windows::Forms::Button^  plusBtn;


	private: System::ComponentModel::BackgroundWorker^  loadResultsBackgroundWorker;

	private: System::ComponentModel::BackgroundWorker^  progressBarBackgroundWorker;
	private: System::Windows::Forms::TabPage^  loadingPageTab;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  loadingLabel;
	private: System::Windows::Forms::Button^  toSearchFolderFromSaveprofile;
	private: System::Windows::Forms::Button^  toHomeFromSaveprofile;
	private: System::Windows::Forms::Label^  namePersonLabel;
	private: System::Windows::Forms::TextBox^  saveProfileTextBox;
	private: System::ComponentModel::BackgroundWorker^  saveProfileBackgroundWorker;
	private: System::Windows::Forms::PictureBox^  loadingGif;
	private: System::Windows::Forms::Label^  loadingGifLabel;
	private: System::Windows::Forms::TabPage^  finishTab;



	private: System::Windows::Forms::Label^  previousProfileImagesLabel;
	private: System::Windows::Forms::TextBox^  desciption;



	private: System::Windows::Forms::PictureBox^  imgProfileSilhouette;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  finishMessage;
	private: System::Windows::Forms::TextBox^  descriptionTextBox;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	private: System::Windows::Forms::Button^  finishCloseBtn;
	private: System::Windows::Forms::Button^  finishHomeBtn;
private: System::Windows::Forms::Label^  label2;










	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(OpeningMenu::typeid));
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->openMenutab = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->previousProfileImagesLabel = (gcnew System::Windows::Forms::Label());
			this->desciption = (gcnew System::Windows::Forms::TextBox());
			this->previousProfileLabel = (gcnew System::Windows::Forms::Label());
			this->subjectTextBox = (gcnew System::Windows::Forms::TextBox());
			this->selectFilesButton = (gcnew System::Windows::Forms::Button());
			this->openFilesButton = (gcnew System::Windows::Forms::Button());
			this->chooseProfilebtn = (gcnew System::Windows::Forms::Button());
			this->profilesListView = (gcnew System::Windows::Forms::ListView());
			this->imgProfileSilhouette = (gcnew System::Windows::Forms::PictureBox());
			this->saveProfileTab = (gcnew System::Windows::Forms::TabPage());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->loadingGifLabel = (gcnew System::Windows::Forms::Label());
			this->loadingGif = (gcnew System::Windows::Forms::PictureBox());
			this->toSearchFolderFromSaveprofile = (gcnew System::Windows::Forms::Button());
			this->toHomeFromSaveprofile = (gcnew System::Windows::Forms::Button());
			this->namePersonLabel = (gcnew System::Windows::Forms::Label());
			this->saveProfileTextBox = (gcnew System::Windows::Forms::TextBox());
			this->searchResultstab = (gcnew System::Windows::Forms::TabPage());
			this->resultsFinishBtn = (gcnew System::Windows::Forms::Button());
			this->resultsBackBtn = (gcnew System::Windows::Forms::Button());
			this->noResultsLabel = (gcnew System::Windows::Forms::Label());
			this->selectRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->unselectRadioBtn = (gcnew System::Windows::Forms::RadioButton());
			this->btnMoveS = (gcnew System::Windows::Forms::Button());
			this->btnDeleteS = (gcnew System::Windows::Forms::Button());
			this->resultsListView = (gcnew System::Windows::Forms::ListView());
			this->searchFoldertab = (gcnew System::Windows::Forms::TabPage());
			this->descriptionTextBox = (gcnew System::Windows::Forms::TextBox());
			this->plusBtn = (gcnew System::Windows::Forms::Button());
			this->folderTextbox3 = (gcnew System::Windows::Forms::TextBox());
			this->chooseFolderBtn3 = (gcnew System::Windows::Forms::Button());
			this->folderTextbox2 = (gcnew System::Windows::Forms::TextBox());
			this->chooseFolderBtn2 = (gcnew System::Windows::Forms::Button());
			this->backToOpen = (gcnew System::Windows::Forms::Button());
			this->viewResultsbtn = (gcnew System::Windows::Forms::Button());
			this->folderTextbox = (gcnew System::Windows::Forms::TextBox());
			this->chooseFolderbtn = (gcnew System::Windows::Forms::Button());
			this->loadingPageTab = (gcnew System::Windows::Forms::TabPage());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->loadingLabel = (gcnew System::Windows::Forms::Label());
			this->finishTab = (gcnew System::Windows::Forms::TabPage());
			this->finishHomeBtn = (gcnew System::Windows::Forms::Button());
			this->finishCloseBtn = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->finishMessage = (gcnew System::Windows::Forms::TextBox());
			this->resultsImagelist = (gcnew System::Windows::Forms::ImageList(this->components));
			this->profilesImageList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->folderBrowserDialog3 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->loadResultsBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->progressBarBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->saveProfileBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl1->SuspendLayout();
			this->openMenutab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imgProfileSilhouette))->BeginInit();
			this->saveProfileTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loadingGif))->BeginInit();
			this->searchResultstab->SuspendLayout();
			this->searchFoldertab->SuspendLayout();
			this->loadingPageTab->SuspendLayout();
			this->finishTab->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->tabControl1->Controls->Add(this->openMenutab);
			this->tabControl1->Controls->Add(this->saveProfileTab);
			this->tabControl1->Controls->Add(this->searchResultstab);
			this->tabControl1->Controls->Add(this->searchFoldertab);
			this->tabControl1->Controls->Add(this->loadingPageTab);
			this->tabControl1->Controls->Add(this->finishTab);
			this->tabControl1->ItemSize = System::Drawing::Size(0, 1);
			this->tabControl1->Location = System::Drawing::Point(1, 1);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(649, 378);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 6;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &OpeningMenu::tabControl1_Selected);
			// 
			// openMenutab
			// 
			this->openMenutab->BackColor = System::Drawing::Color::White;
			this->openMenutab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->openMenutab->Controls->Add(this->pictureBox1);
			this->openMenutab->Controls->Add(this->previousProfileImagesLabel);
			this->openMenutab->Controls->Add(this->desciption);
			this->openMenutab->Controls->Add(this->previousProfileLabel);
			this->openMenutab->Controls->Add(this->subjectTextBox);
			this->openMenutab->Controls->Add(this->selectFilesButton);
			this->openMenutab->Controls->Add(this->openFilesButton);
			this->openMenutab->Controls->Add(this->chooseProfilebtn);
			this->openMenutab->Controls->Add(this->profilesListView);
			this->openMenutab->Controls->Add(this->imgProfileSilhouette);
			this->openMenutab->Location = System::Drawing::Point(4, 5);
			this->openMenutab->Name = L"openMenutab";
			this->openMenutab->Padding = System::Windows::Forms::Padding(3);
			this->openMenutab->Size = System::Drawing::Size(641, 369);
			this->openMenutab->TabIndex = 0;
			this->openMenutab->Text = L"opening menu";
			this->openMenutab->Click += gcnew System::EventHandler(this, &OpeningMenu::openMenutab_Click);
			this->openMenutab->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OpeningMenu::OnPaint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(140, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(176, 47);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 22;
			this->pictureBox1->TabStop = false;
			// 
			// previousProfileImagesLabel
			// 
			this->previousProfileImagesLabel->AutoSize = true;
			this->previousProfileImagesLabel->BackColor = System::Drawing::Color::White;
			this->previousProfileImagesLabel->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 6.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->previousProfileImagesLabel->Location = System::Drawing::Point(472, 161);
			this->previousProfileImagesLabel->Name = L"previousProfileImagesLabel";
			this->previousProfileImagesLabel->Size = System::Drawing::Size(134, 11);
			this->previousProfileImagesLabel->TabIndex = 19;
			this->previousProfileImagesLabel->Text = L"No profiles have been created.";
			this->previousProfileImagesLabel->Visible = false;
			// 
			// desciption
			// 
			this->desciption->BackColor = System::Drawing::Color::White;
			this->desciption->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->desciption->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->desciption->Location = System::Drawing::Point(113, 240);
			this->desciption->Multiline = true;
			this->desciption->Name = L"desciption";
			this->desciption->ReadOnly = true;
			this->desciption->Size = System::Drawing::Size(227, 48);
			this->desciption->TabIndex = 18;
			this->desciption->Text = L"Upload at least 7 images of the person you want to find and then press Go and we "
				L"will find all the images you have that contain that person.";
			// 
			// previousProfileLabel
			// 
			this->previousProfileLabel->AutoSize = true;
			this->previousProfileLabel->BackColor = System::Drawing::Color::White;
			this->previousProfileLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->previousProfileLabel->Location = System::Drawing::Point(458, 38);
			this->previousProfileLabel->Name = L"previousProfileLabel";
			this->previousProfileLabel->Size = System::Drawing::Size(167, 15);
			this->previousProfileLabel->TabIndex = 16;
			this->previousProfileLabel->Text = L"Use a previously used person";
			this->previousProfileLabel->Click += gcnew System::EventHandler(this, &OpeningMenu::previousProfileLabel_Click);
			// 
			// subjectTextBox
			// 
			this->subjectTextBox->Location = System::Drawing::Point(180, 292);
			this->subjectTextBox->Name = L"subjectTextBox";
			this->subjectTextBox->Size = System::Drawing::Size(167, 20);
			this->subjectTextBox->TabIndex = 15;
			// 
			// selectFilesButton
			// 
			this->selectFilesButton->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->selectFilesButton->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->selectFilesButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"selectFilesButton.Image")));
			this->selectFilesButton->Location = System::Drawing::Point(190, 318);
			this->selectFilesButton->Name = L"selectFilesButton";
			this->selectFilesButton->Size = System::Drawing::Size(130, 37);
			this->selectFilesButton->TabIndex = 13;
			this->selectFilesButton->Text = L"Go!";
			this->selectFilesButton->UseVisualStyleBackColor = true;
			this->selectFilesButton->Click += gcnew System::EventHandler(this, &OpeningMenu::selectFilesButton_Click_1);
			// 
			// openFilesButton
			// 
			this->openFilesButton->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->openFilesButton->Location = System::Drawing::Point(83, 291);
			this->openFilesButton->Name = L"openFilesButton";
			this->openFilesButton->Size = System::Drawing::Size(103, 22);
			this->openFilesButton->TabIndex = 14;
			this->openFilesButton->Text = L"Upload Images";
			this->openFilesButton->UseVisualStyleBackColor = true;
			this->openFilesButton->Click += gcnew System::EventHandler(this, &OpeningMenu::openFilesButton_Click_1);
			// 
			// chooseProfilebtn
			// 
			this->chooseProfilebtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->chooseProfilebtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->chooseProfilebtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chooseProfilebtn.Image")));
			this->chooseProfilebtn->Location = System::Drawing::Point(504, 268);
			this->chooseProfilebtn->Name = L"chooseProfilebtn";
			this->chooseProfilebtn->Size = System::Drawing::Size(87, 33);
			this->chooseProfilebtn->TabIndex = 10;
			this->chooseProfilebtn->Text = L"Select Profile";
			this->chooseProfilebtn->UseVisualStyleBackColor = true;
			this->chooseProfilebtn->Click += gcnew System::EventHandler(this, &OpeningMenu::chooseProfilebtn_Click_1);
			// 
			// profilesListView
			// 
			this->profilesListView->Location = System::Drawing::Point(467, 56);
			this->profilesListView->Name = L"profilesListView";
			this->profilesListView->Size = System::Drawing::Size(154, 206);
			this->profilesListView->TabIndex = 9;
			this->profilesListView->UseCompatibleStateImageBehavior = false;
			this->profilesListView->SelectedIndexChanged += gcnew System::EventHandler(this, &OpeningMenu::profilesListView_SelectedIndexChanged);
			// 
			// imgProfileSilhouette
			// 
			this->imgProfileSilhouette->BackColor = System::Drawing::Color::White;
			this->imgProfileSilhouette->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"imgProfileSilhouette.Image")));
			this->imgProfileSilhouette->Location = System::Drawing::Point(120, 61);
			this->imgProfileSilhouette->Name = L"imgProfileSilhouette";
			this->imgProfileSilhouette->Size = System::Drawing::Size(215, 178);
			this->imgProfileSilhouette->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->imgProfileSilhouette->TabIndex = 21;
			this->imgProfileSilhouette->TabStop = false;
			// 
			// saveProfileTab
			// 
			this->saveProfileTab->BackColor = System::Drawing::Color::White;
			this->saveProfileTab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->saveProfileTab->Controls->Add(this->textBox1);
			this->saveProfileTab->Controls->Add(this->loadingGifLabel);
			this->saveProfileTab->Controls->Add(this->loadingGif);
			this->saveProfileTab->Controls->Add(this->toSearchFolderFromSaveprofile);
			this->saveProfileTab->Controls->Add(this->toHomeFromSaveprofile);
			this->saveProfileTab->Controls->Add(this->namePersonLabel);
			this->saveProfileTab->Controls->Add(this->saveProfileTextBox);
			this->saveProfileTab->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->saveProfileTab->Location = System::Drawing::Point(4, 5);
			this->saveProfileTab->Name = L"saveProfileTab";
			this->saveProfileTab->Padding = System::Windows::Forms::Padding(3);
			this->saveProfileTab->Size = System::Drawing::Size(641, 369);
			this->saveProfileTab->TabIndex = 3;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(7, 125);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(252, 20);
			this->textBox1->TabIndex = 10;
			this->textBox1->Text = L"Please enter the name of this person";
			// 
			// loadingGifLabel
			// 
			this->loadingGifLabel->AutoSize = true;
			this->loadingGifLabel->BackColor = System::Drawing::Color::White;
			this->loadingGifLabel->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->loadingGifLabel->Location = System::Drawing::Point(176, 81);
			this->loadingGifLabel->Name = L"loadingGifLabel";
			this->loadingGifLabel->Size = System::Drawing::Size(195, 15);
			this->loadingGifLabel->TabIndex = 5;
			this->loadingGifLabel->Text = L"One moment, saving profile...";
			this->loadingGifLabel->Visible = false;
			// 
			// loadingGif
			// 
			this->loadingGif->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loadingGif.Image")));
			this->loadingGif->Location = System::Drawing::Point(280, 115);
			this->loadingGif->Name = L"loadingGif";
			this->loadingGif->Size = System::Drawing::Size(112, 105);
			this->loadingGif->TabIndex = 4;
			this->loadingGif->TabStop = false;
			this->loadingGif->Visible = false;
			// 
			// toSearchFolderFromSaveprofile
			// 
			this->toSearchFolderFromSaveprofile->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->toSearchFolderFromSaveprofile->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->toSearchFolderFromSaveprofile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toSearchFolderFromSaveprofile.Image")));
			this->toSearchFolderFromSaveprofile->Location = System::Drawing::Point(499, 295);
			this->toSearchFolderFromSaveprofile->Name = L"toSearchFolderFromSaveprofile";
			this->toSearchFolderFromSaveprofile->Size = System::Drawing::Size(102, 51);
			this->toSearchFolderFromSaveprofile->TabIndex = 3;
			this->toSearchFolderFromSaveprofile->Text = L"Next";
			this->toSearchFolderFromSaveprofile->UseVisualStyleBackColor = true;
			this->toSearchFolderFromSaveprofile->Click += gcnew System::EventHandler(this, &OpeningMenu::toSearchFolderFromSaveprofile_Click);
			// 
			// toHomeFromSaveprofile
			// 
			this->toHomeFromSaveprofile->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->toHomeFromSaveprofile->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->toHomeFromSaveprofile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toHomeFromSaveprofile.Image")));
			this->toHomeFromSaveprofile->Location = System::Drawing::Point(33, 295);
			this->toHomeFromSaveprofile->Name = L"toHomeFromSaveprofile";
			this->toHomeFromSaveprofile->Size = System::Drawing::Size(102, 51);
			this->toHomeFromSaveprofile->TabIndex = 2;
			this->toHomeFromSaveprofile->Text = L"Back";
			this->toHomeFromSaveprofile->UseVisualStyleBackColor = true;
			this->toHomeFromSaveprofile->Click += gcnew System::EventHandler(this, &OpeningMenu::toHomeFromSaveprofile_Click);
			// 
			// namePersonLabel
			// 
			this->namePersonLabel->BackColor = System::Drawing::Color::White;
			this->namePersonLabel->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->namePersonLabel->Location = System::Drawing::Point(166, 167);
			this->namePersonLabel->Name = L"namePersonLabel";
			this->namePersonLabel->Size = System::Drawing::Size(45, 18);
			this->namePersonLabel->TabIndex = 1;
			this->namePersonLabel->Text = L"Name:";
			// 
			// saveProfileTextBox
			// 
			this->saveProfileTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->saveProfileTextBox->Location = System::Drawing::Point(217, 159);
			this->saveProfileTextBox->Multiline = true;
			this->saveProfileTextBox->Name = L"saveProfileTextBox";
			this->saveProfileTextBox->Size = System::Drawing::Size(231, 25);
			this->saveProfileTextBox->TabIndex = 0;
			this->saveProfileTextBox->TextChanged += gcnew System::EventHandler(this, &OpeningMenu::saveProfileTextBox_TextChanged);
			// 
			// searchResultstab
			// 
			this->searchResultstab->BackColor = System::Drawing::Color::White;
			this->searchResultstab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->searchResultstab->Controls->Add(this->resultsFinishBtn);
			this->searchResultstab->Controls->Add(this->resultsBackBtn);
			this->searchResultstab->Controls->Add(this->noResultsLabel);
			this->searchResultstab->Controls->Add(this->selectRadioBtn);
			this->searchResultstab->Controls->Add(this->unselectRadioBtn);
			this->searchResultstab->Controls->Add(this->btnMoveS);
			this->searchResultstab->Controls->Add(this->btnDeleteS);
			this->searchResultstab->Controls->Add(this->resultsListView);
			this->searchResultstab->Location = System::Drawing::Point(4, 5);
			this->searchResultstab->Name = L"searchResultstab";
			this->searchResultstab->Padding = System::Windows::Forms::Padding(3);
			this->searchResultstab->Size = System::Drawing::Size(641, 369);
			this->searchResultstab->TabIndex = 4;
			this->searchResultstab->Text = L"searchresultstab";
			// 
			// resultsFinishBtn
			// 
			this->resultsFinishBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->resultsFinishBtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->resultsFinishBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"resultsFinishBtn.Image")));
			this->resultsFinishBtn->Location = System::Drawing::Point(499, 295);
			this->resultsFinishBtn->Name = L"resultsFinishBtn";
			this->resultsFinishBtn->Size = System::Drawing::Size(102, 51);
			this->resultsFinishBtn->TabIndex = 14;
			this->resultsFinishBtn->Text = L"Finish";
			this->resultsFinishBtn->UseVisualStyleBackColor = true;
			this->resultsFinishBtn->Click += gcnew System::EventHandler(this, &OpeningMenu::resultsFinishBtn_Click);
			// 
			// resultsBackBtn
			// 
			this->resultsBackBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resultsBackBtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->resultsBackBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"resultsBackBtn.Image")));
			this->resultsBackBtn->Location = System::Drawing::Point(33, 295);
			this->resultsBackBtn->Name = L"resultsBackBtn";
			this->resultsBackBtn->Size = System::Drawing::Size(102, 51);
			this->resultsBackBtn->TabIndex = 13;
			this->resultsBackBtn->Text = L"Back";
			this->resultsBackBtn->UseVisualStyleBackColor = true;
			this->resultsBackBtn->Click += gcnew System::EventHandler(this, &OpeningMenu::resultsBackBtn_Click);
			// 
			// noResultsLabel
			// 
			this->noResultsLabel->AutoSize = true;
			this->noResultsLabel->BackColor = System::Drawing::Color::White;
			this->noResultsLabel->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->noResultsLabel->Location = System::Drawing::Point(225, 164);
			this->noResultsLabel->Name = L"noResultsLabel";
			this->noResultsLabel->Size = System::Drawing::Size(216, 14);
			this->noResultsLabel->TabIndex = 12;
			this->noResultsLabel->Text = L"No images of the person were found";
			this->noResultsLabel->Visible = false;
			// 
			// selectRadioBtn
			// 
			this->selectRadioBtn->AutoSize = true;
			this->selectRadioBtn->BackColor = System::Drawing::Color::White;
			this->selectRadioBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->selectRadioBtn->Location = System::Drawing::Point(130, 25);
			this->selectRadioBtn->Name = L"selectRadioBtn";
			this->selectRadioBtn->Size = System::Drawing::Size(79, 18);
			this->selectRadioBtn->TabIndex = 11;
			this->selectRadioBtn->TabStop = true;
			this->selectRadioBtn->Text = L"Select All";
			this->selectRadioBtn->UseVisualStyleBackColor = false;
			this->selectRadioBtn->CheckedChanged += gcnew System::EventHandler(this, &OpeningMenu::selectRadioBtn_CheckedChanged);
			// 
			// unselectRadioBtn
			// 
			this->unselectRadioBtn->AutoSize = true;
			this->unselectRadioBtn->BackColor = System::Drawing::Color::White;
			this->unselectRadioBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->unselectRadioBtn->Location = System::Drawing::Point(26, 25);
			this->unselectRadioBtn->Name = L"unselectRadioBtn";
			this->unselectRadioBtn->Size = System::Drawing::Size(94, 18);
			this->unselectRadioBtn->TabIndex = 10;
			this->unselectRadioBtn->TabStop = true;
			this->unselectRadioBtn->Text = L"Unselect All";
			this->unselectRadioBtn->UseVisualStyleBackColor = false;
			this->unselectRadioBtn->CheckedChanged += gcnew System::EventHandler(this, &OpeningMenu::unselectRadioBtn_CheckedChanged);
			// 
			// btnMoveS
			// 
			this->btnMoveS->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveS->Location = System::Drawing::Point(304, 282);
			this->btnMoveS->Name = L"btnMoveS";
			this->btnMoveS->Size = System::Drawing::Size(90, 29);
			this->btnMoveS->TabIndex = 8;
			this->btnMoveS->Text = L"Move Images";
			this->btnMoveS->UseVisualStyleBackColor = true;
			this->btnMoveS->Click += gcnew System::EventHandler(this, &OpeningMenu::btnMoveS_Click);
			// 
			// btnDeleteS
			// 
			this->btnDeleteS->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDeleteS->Location = System::Drawing::Point(198, 282);
			this->btnDeleteS->Name = L"btnDeleteS";
			this->btnDeleteS->Size = System::Drawing::Size(100, 29);
			this->btnDeleteS->TabIndex = 7;
			this->btnDeleteS->Text = L"Delete Images";
			this->btnDeleteS->UseVisualStyleBackColor = true;
			this->btnDeleteS->Click += gcnew System::EventHandler(this, &OpeningMenu::btnDeleteS_Click);
			// 
			// resultsListView
			// 
			this->resultsListView->Location = System::Drawing::Point(21, 48);
			this->resultsListView->Name = L"resultsListView";
			this->resultsListView->Size = System::Drawing::Size(583, 228);
			this->resultsListView->TabIndex = 5;
			this->resultsListView->UseCompatibleStateImageBehavior = false;
			this->resultsListView->SelectedIndexChanged += gcnew System::EventHandler(this, &OpeningMenu::resultsListView_SelectedIndexChanged);
			// 
			// searchFoldertab
			// 
			this->searchFoldertab->BackColor = System::Drawing::Color::White;
			this->searchFoldertab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->searchFoldertab->Controls->Add(this->descriptionTextBox);
			this->searchFoldertab->Controls->Add(this->plusBtn);
			this->searchFoldertab->Controls->Add(this->folderTextbox3);
			this->searchFoldertab->Controls->Add(this->chooseFolderBtn3);
			this->searchFoldertab->Controls->Add(this->folderTextbox2);
			this->searchFoldertab->Controls->Add(this->chooseFolderBtn2);
			this->searchFoldertab->Controls->Add(this->backToOpen);
			this->searchFoldertab->Controls->Add(this->viewResultsbtn);
			this->searchFoldertab->Controls->Add(this->folderTextbox);
			this->searchFoldertab->Controls->Add(this->chooseFolderbtn);
			this->searchFoldertab->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->searchFoldertab->Location = System::Drawing::Point(4, 5);
			this->searchFoldertab->Name = L"searchFoldertab";
			this->searchFoldertab->Padding = System::Windows::Forms::Padding(3);
			this->searchFoldertab->Size = System::Drawing::Size(641, 369);
			this->searchFoldertab->TabIndex = 5;
			this->searchFoldertab->Text = L"choosefolder";
			// 
			// descriptionTextBox
			// 
			this->descriptionTextBox->BackColor = System::Drawing::Color::White;
			this->descriptionTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->descriptionTextBox->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->descriptionTextBox->Location = System::Drawing::Point(12, 76);
			this->descriptionTextBox->Multiline = true;
			this->descriptionTextBox->Name = L"descriptionTextBox";
			this->descriptionTextBox->ReadOnly = true;
			this->descriptionTextBox->Size = System::Drawing::Size(493, 20);
			this->descriptionTextBox->TabIndex = 9;
			this->descriptionTextBox->Text = L"Choose up to 3 folders for Face Finder to search through to find the person you w"
				L"ant.";
			// 
			// plusBtn
			// 
			this->plusBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->plusBtn->FlatAppearance->BorderSize = 0;
			this->plusBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->plusBtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->plusBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"plusBtn.Image")));
			this->plusBtn->Location = System::Drawing::Point(309, 135);
			this->plusBtn->Name = L"plusBtn";
			this->plusBtn->Size = System::Drawing::Size(100, 38);
			this->plusBtn->TabIndex = 8;
			this->plusBtn->Text = L"More Folders";
			this->plusBtn->UseVisualStyleBackColor = true;
			this->plusBtn->Click += gcnew System::EventHandler(this, &OpeningMenu::plusBtn_Click);
			// 
			// folderTextbox3
			// 
			this->folderTextbox3->Location = System::Drawing::Point(283, 259);
			this->folderTextbox3->Multiline = true;
			this->folderTextbox3->Name = L"folderTextbox3";
			this->folderTextbox3->Size = System::Drawing::Size(231, 25);
			this->folderTextbox3->TabIndex = 7;
			this->folderTextbox3->Visible = false;
			// 
			// chooseFolderBtn3
			// 
			this->chooseFolderBtn3->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->chooseFolderBtn3->Location = System::Drawing::Point(175, 258);
			this->chooseFolderBtn3->Name = L"chooseFolderBtn3";
			this->chooseFolderBtn3->Size = System::Drawing::Size(111, 27);
			this->chooseFolderBtn3->TabIndex = 6;
			this->chooseFolderBtn3->Text = L"Choose Folder 3";
			this->chooseFolderBtn3->UseVisualStyleBackColor = true;
			this->chooseFolderBtn3->Visible = false;
			this->chooseFolderBtn3->Click += gcnew System::EventHandler(this, &OpeningMenu::chooseFolderBtn3_Click);
			// 
			// folderTextbox2
			// 
			this->folderTextbox2->Location = System::Drawing::Point(283, 184);
			this->folderTextbox2->Multiline = true;
			this->folderTextbox2->Name = L"folderTextbox2";
			this->folderTextbox2->Size = System::Drawing::Size(231, 25);
			this->folderTextbox2->TabIndex = 5;
			this->folderTextbox2->Visible = false;
			// 
			// chooseFolderBtn2
			// 
			this->chooseFolderBtn2->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->chooseFolderBtn2->Location = System::Drawing::Point(175, 183);
			this->chooseFolderBtn2->Name = L"chooseFolderBtn2";
			this->chooseFolderBtn2->Size = System::Drawing::Size(111, 27);
			this->chooseFolderBtn2->TabIndex = 4;
			this->chooseFolderBtn2->Text = L"Choose Folder 2";
			this->chooseFolderBtn2->UseVisualStyleBackColor = true;
			this->chooseFolderBtn2->Visible = false;
			this->chooseFolderBtn2->Click += gcnew System::EventHandler(this, &OpeningMenu::chooseFolderBtn2_Click);
			// 
			// backToOpen
			// 
			this->backToOpen->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->backToOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"backToOpen.Image")));
			this->backToOpen->Location = System::Drawing::Point(33, 295);
			this->backToOpen->Name = L"backToOpen";
			this->backToOpen->Size = System::Drawing::Size(102, 51);
			this->backToOpen->TabIndex = 3;
			this->backToOpen->Text = L"Back";
			this->backToOpen->UseVisualStyleBackColor = true;
			this->backToOpen->Click += gcnew System::EventHandler(this, &OpeningMenu::backToOpen_Click);
			// 
			// viewResultsbtn
			// 
			this->viewResultsbtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->viewResultsbtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"viewResultsbtn.Image")));
			this->viewResultsbtn->Location = System::Drawing::Point(499, 295);
			this->viewResultsbtn->Name = L"viewResultsbtn";
			this->viewResultsbtn->Size = System::Drawing::Size(102, 51);
			this->viewResultsbtn->TabIndex = 2;
			this->viewResultsbtn->Text = L"Go!";
			this->viewResultsbtn->UseVisualStyleBackColor = true;
			this->viewResultsbtn->Click += gcnew System::EventHandler(this, &OpeningMenu::viewResultsbtn_Click);
			// 
			// folderTextbox
			// 
			this->folderTextbox->Location = System::Drawing::Point(283, 103);
			this->folderTextbox->Multiline = true;
			this->folderTextbox->Name = L"folderTextbox";
			this->folderTextbox->Size = System::Drawing::Size(231, 25);
			this->folderTextbox->TabIndex = 1;
			this->folderTextbox->TextChanged += gcnew System::EventHandler(this, &OpeningMenu::folderTextbox_TextChanged);
			// 
			// chooseFolderbtn
			// 
			this->chooseFolderbtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->chooseFolderbtn->Location = System::Drawing::Point(175, 102);
			this->chooseFolderbtn->Name = L"chooseFolderbtn";
			this->chooseFolderbtn->Size = System::Drawing::Size(111, 27);
			this->chooseFolderbtn->TabIndex = 0;
			this->chooseFolderbtn->Text = L"Choose Folder";
			this->chooseFolderbtn->UseVisualStyleBackColor = true;
			this->chooseFolderbtn->Click += gcnew System::EventHandler(this, &OpeningMenu::chooseFolderbtn_Click);
			// 
			// loadingPageTab
			// 
			this->loadingPageTab->BackColor = System::Drawing::Color::White;
			this->loadingPageTab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->loadingPageTab->Controls->Add(this->label2);
			this->loadingPageTab->Controls->Add(this->progressBar1);
			this->loadingPageTab->Controls->Add(this->loadingLabel);
			this->loadingPageTab->Location = System::Drawing::Point(4, 5);
			this->loadingPageTab->Name = L"loadingPageTab";
			this->loadingPageTab->Padding = System::Windows::Forms::Padding(3);
			this->loadingPageTab->Size = System::Drawing::Size(641, 369);
			this->loadingPageTab->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::White;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(219, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(204, 14);
			this->label2->TabIndex = 22;
			this->label2->Text = L"We are finding your images now...";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(219, 145);
			this->progressBar1->Maximum = 105;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(204, 50);
			this->progressBar1->TabIndex = 21;
			// 
			// loadingLabel
			// 
			this->loadingLabel->AutoSize = true;
			this->loadingLabel->BackColor = System::Drawing::Color::White;
			this->loadingLabel->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loadingLabel->Location = System::Drawing::Point(198, 231);
			this->loadingLabel->Name = L"loadingLabel";
			this->loadingLabel->Size = System::Drawing::Size(249, 14);
			this->loadingLabel->TabIndex = 20;
			this->loadingLabel->Text = L"...this may take approximately 1 minute(s)";
			// 
			// finishTab
			// 
			this->finishTab->BackColor = System::Drawing::Color::White;
			this->finishTab->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->finishTab->Controls->Add(this->finishHomeBtn);
			this->finishTab->Controls->Add(this->finishCloseBtn);
			this->finishTab->Controls->Add(this->pictureBox2);
			this->finishTab->Controls->Add(this->finishMessage);
			this->finishTab->Location = System::Drawing::Point(4, 5);
			this->finishTab->Name = L"finishTab";
			this->finishTab->Padding = System::Windows::Forms::Padding(3);
			this->finishTab->Size = System::Drawing::Size(641, 369);
			this->finishTab->TabIndex = 7;
			// 
			// finishHomeBtn
			// 
			this->finishHomeBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->finishHomeBtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->finishHomeBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"finishHomeBtn.Image")));
			this->finishHomeBtn->Location = System::Drawing::Point(31, 312);
			this->finishHomeBtn->Name = L"finishHomeBtn";
			this->finishHomeBtn->Size = System::Drawing::Size(100, 41);
			this->finishHomeBtn->TabIndex = 25;
			this->finishHomeBtn->Text = L"Home";
			this->finishHomeBtn->UseVisualStyleBackColor = true;
			this->finishHomeBtn->Click += gcnew System::EventHandler(this, &OpeningMenu::finishHomeBtn_Click);
			// 
			// finishCloseBtn
			// 
			this->finishCloseBtn->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->finishCloseBtn->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->finishCloseBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"finishCloseBtn.Image")));
			this->finishCloseBtn->Location = System::Drawing::Point(514, 312);
			this->finishCloseBtn->Name = L"finishCloseBtn";
			this->finishCloseBtn->Size = System::Drawing::Size(100, 41);
			this->finishCloseBtn->TabIndex = 24;
			this->finishCloseBtn->Text = L"Close";
			this->finishCloseBtn->UseVisualStyleBackColor = true;
			this->finishCloseBtn->Click += gcnew System::EventHandler(this, &OpeningMenu::finishCloseBtn_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::White;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(205, 28);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(238, 78);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 23;
			this->pictureBox2->TabStop = false;
			// 
			// finishMessage
			// 
			this->finishMessage->BackColor = System::Drawing::Color::White;
			this->finishMessage->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->finishMessage->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->finishMessage->Location = System::Drawing::Point(162, 148);
			this->finishMessage->Multiline = true;
			this->finishMessage->Name = L"finishMessage";
			this->finishMessage->Size = System::Drawing::Size(328, 69);
			this->finishMessage->TabIndex = 2;
			this->finishMessage->Text = L"You have finished moving and/or deleting all images that contained the person you"
				L" were looking for. Click Home to go back to the Home page or Close to exit Face "
				L"Finder.";
			// 
			// resultsImagelist
			// 
			this->resultsImagelist->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->resultsImagelist->ImageSize = System::Drawing::Size(16, 16);
			this->resultsImagelist->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// profilesImageList
			// 
			this->profilesImageList->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->profilesImageList->ImageSize = System::Drawing::Size(16, 16);
			this->profilesImageList->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// loadResultsBackgroundWorker
			// 
			this->loadResultsBackgroundWorker->WorkerSupportsCancellation = true;
			this->loadResultsBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &OpeningMenu::loadResultsBackgroundWorker_DoWork);
			// 
			// progressBarBackgroundWorker
			// 
			this->progressBarBackgroundWorker->WorkerSupportsCancellation = true;
			this->progressBarBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &OpeningMenu::progressBarBackgroundWorker_DoWork);
			// 
			// saveProfileBackgroundWorker
			// 
			this->saveProfileBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &OpeningMenu::saveProfileBackgroundWorker_DoWork);
			// 
			// OpeningMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(647, 376);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(663, 415);
			this->MinimumSize = System::Drawing::Size(663, 415);
			this->Name = L"OpeningMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Face Finder";
			this->Load += gcnew System::EventHandler(this, &OpeningMenu::OpeningMenu_Load);
			this->tabControl1->ResumeLayout(false);
			this->openMenutab->ResumeLayout(false);
			this->openMenutab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imgProfileSilhouette))->EndInit();
			this->saveProfileTab->ResumeLayout(false);
			this->saveProfileTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->loadingGif))->EndInit();
			this->searchResultstab->ResumeLayout(false);
			this->searchResultstab->PerformLayout();
			this->searchFoldertab->ResumeLayout(false);
			this->searchFoldertab->PerformLayout();
			this->loadingPageTab->ResumeLayout(false);
			this->loadingPageTab->PerformLayout();
			this->finishTab->ResumeLayout(false);
			this->finishTab->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void OpeningMenu_Load(System::Object^  sender, System::EventArgs^  e) {
				 //loadingGif->Image = Image::FromFile("spiffygif_94x94.gif");
				 //imgProfileSilhouette->Image = Image::FromFile("profilepicture.png");
				 resultsListView->Scrollable = true;
				 resultsImagelist = gcnew ImageList;
				 resultsImagelist->ColorDepth = ColorDepth::Depth32Bit;
				 resultsImagelist->ImageSize = System::Drawing::Size(65, 65); // set the display parameters of the list view
				 resultsListView->LargeImageList = resultsImagelist; //adds the results image list to the list view, allows the liswt view to display images
				 resultsListView->CheckBoxes = true; //adds check boxes to each imag in the list view
				 loadProfilesLV(); // loads the profile listview (located on the used profiles tab)
				 FileComputations::getAppDataFolder();
	}

	private: System::Void tabControl1_Selected(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^ e) {
				 // this method prevents users from selecting any tab accept the tabs permitted for each specific page
				 if (GlobalVariables::getTabIndex() == 0) { //homepage
					 if (e->TabPage == loadingPageTab || e->TabPage == finishTab || e->TabPage == searchResultstab || e->TabPage == searchFoldertab || e->TabPage == saveProfileTab) {
						 e->Cancel = true;
					 }
				 }
				 else if (GlobalVariables::getTabIndex() == 1) { //newprofile
					 if (e->TabPage == loadingPageTab || e->TabPage == finishTab || e->TabPage == searchResultstab || e->TabPage == searchFoldertab || e->TabPage == saveProfileTab || e->TabPage == openMenutab) {
						 e->Cancel = true;
					 }
				 }

				 else if (GlobalVariables::getTabIndex() == 3) { //save profile
					 if (e->TabPage == loadingPageTab || e->TabPage == loadingPageTab || e->TabPage == finishTab || e->TabPage == searchFoldertab || e->TabPage == openMenutab) {
						 e->Cancel = true;
					 }
				 }
				 else if (GlobalVariables::getTabIndex() == 4) { //search folder tab
					 if (e->TabPage == loadingPageTab || e->TabPage == finishTab || e->TabPage == searchResultstab || e->TabPage == openMenutab) {
						 e->Cancel = true;
					 }
				 }
				 else if (GlobalVariables::getTabIndex() == 5) { //searchresults
					 if (e->TabPage == loadingPageTab || e->TabPage == finishTab || e->TabPage == saveProfileTab || e->TabPage == openMenutab || e->TabPage == searchFoldertab) {
						 e->Cancel = true;
					 }
					 else if (GlobalVariables::getTabIndex() == 6) { //loadingtab
						 if (e->TabPage == searchResultstab || e->TabPage == finishTab || e->TabPage == saveProfileTab || e->TabPage == openMenutab || e->TabPage == searchFoldertab) {
							 e->Cancel = true;
						 }
					 }
					 else if (GlobalVariables::getTabIndex() == 7) { //finishtab
						 if (e->TabPage == searchResultstab || e->TabPage == loadingPageTab || e->TabPage == saveProfileTab || e->TabPage == openMenutab || e->TabPage == searchFoldertab) {
							 e->Cancel = true;
						 }
					 }
				 }
	}

	private: System::Void openFilesButton_Click(System::Object^  sender, System::EventArgs^  e) {
	}

			 //----------------------------------------------Opening Menu----------------------------------------------------------//





			 //-----------------------------------------------New Profile----------------------------------------------------------//
	private: System::Void openFilesButton_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 // Set the file dialog to filter for graphics files.

				 //System::Windows::Forms::OpenFileDialog openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog()); 

				 openFileDialog1->Filter =
					 "Images (*.BMP;*.JPG;*.GIF;*.JPEG;*.JP2;*.PNG;*.DIB;*.PBM;*.PPM;*.SR;*.TIFF;*.TIF;*.JPE;*.BMP;*.PGM;*.RAS;)|*.BMP;*.JPG;*.GIF;*.JP2;*.PNG;*.DIB;*.PBM;*.PPM;*.SR;*.TIFF;*.TIF;*.JPE;*.BMP;*.PGM;*.RAS;|" +
					 "All files (*.*)|*.*";
				 //  Allow the user to select multiple images.
				 openFileDialog1->Title = "Image Browser";
				 // allows the user to select multiple images
				 openFileDialog1->Multiselect = true;
				 vector<string> files;
				 String ^ forTextBox = "";
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){

					 //PLEASE NOTE THE FOR LOOP USES A GREATER THAN SIGN
					 for (int i = 0; i < openFileDialog1->SafeFileNames->Length; i++) {
						 forTextBox = forTextBox + ", " + openFileDialog1->SafeFileNames[i]->ToString();
						 string file = msclr::interop::marshal_as<std::string>(openFileDialog1->SafeFileNames[i]->ToString());
						 files.push_back(file);

					 }
				 }

				 GlobalVariables::setProfileImagesToDetectFace(files);
				 // sets the textbox located on the newProfiletab to display the files selected by the user
				 subjectTextBox->Text = forTextBox;

	}

	private: System::Void selectFilesButton_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 vector<string> files;
				 if (GlobalVariables::getProfileImagesToDetectFace().size() >= 7) { // makes sure the user has selected files from which the image profile will be built
					 // the below for loop copies the file paths in openFileDialogue1 into a new vector called "files" 
					 for (int i = 0; i < openFileDialog1->FileNames->Length; i++) {
						 String ^ file = openFileDialog1->FileNames[i]->ToString();
						 string filename;
						 filename = msclr::interop::marshal_as<std::string>(file);
						 toCSV("imageFiles.txt", filename);
						 files.push_back(filename);
					 }



					 if (MessageBox::Show(
						 "Are you sure that you want to upload these images?",
						 "Upload images", MessageBoxButtons::YesNo,
						 MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No) {
					 }
					 else {

						 string thumbnail = msclr::interop::marshal_as<std::string>(openFileDialog1->FileNames[0]->ToString());// converts type "String^" to "string"
						 GlobalVariables::setThumbnail(thumbnail); // sets the thumbnail image to the first element of the openfiledialogue collection
						 GlobalVariables::setProfileImagesToDetectFace(files);
						 GlobalVariables::setProfileSaved("No"); // reset profileSaved Variable to "No"
						 GlobalVariables::setTabIndex(3);
						 this->tabControl1->SelectedTab = saveProfileTab;
					 }
				 }
				 else {
					 MessageBox::Show("Please upload at least 7 images",
						 "Select images", MessageBoxButtons::OK);// if no images have been selected this message box is displayed
				 }
	}

			 // back button, changes back to the opening menu tab
	private: System::Void backToMenu_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setTabIndex(0);
				 //tabIndex = 0;
				 this->tabControl1->SelectedTab = openMenutab;
	}

			 // appears as open button on the  searchFoldertab
	private: System::Void chooseFolderbtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // opens a folderBroswerDialog1 allows user to choose a folder to search
					 folderTextbox->Text = folderBrowserDialog1->SelectedPath;
					 //SETS THE GLOBAL VARIABLE THAT STORES THE IMAGES THAT WILL BE SEARCHED THROUGH TO FIND THE PROFILE
					 GlobalVariables::setFolderChosen(1); // tells the rest of the program that a folder has been chosen
					 //get files from folder
					 //this is my code below to get all the image files from the folder.


				 }
				 else {
					 //folderChosen = 0;
					 GlobalVariables::setFolderChosen(0); // tells the rest of the program that no folder has been chosen
				 }
	}

			 // appears as results button on the searchfodlerTab
	private: System::Void viewResultsbtn_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (GlobalVariables::getFolderChosen() == 1) {
					 string firstFolderName = msclr::interop::marshal_as<std::string>(folderBrowserDialog1->SelectedPath);
					 vector<string> filesToFindPerson = FileComputations::getFilesFromFolder(firstFolderName);
					 int filesToFindPersonIndex = 0;
					 for (int i = 0; i < filesToFindPerson.size(); i++)
					 {
						 filesToFindPerson[i] = firstFolderName + "\\" + filesToFindPerson[i];
						 filesToFindPersonIndex = i;
					 }
					 if (folderTextbox2->Text->Length != 0)
					 {
						 string secondFolderName = msclr::interop::marshal_as<std::string>(folderBrowserDialog2->SelectedPath);
						 vector<string> filesToFindPerson2 = FileComputations::getFilesFromFolder(secondFolderName);
						 filesToFindPersonIndex++;
						 for (int i = 0; i < filesToFindPerson2.size(); i++)
						 {
							 filesToFindPerson.push_back(secondFolderName + "\\" + filesToFindPerson2[i]);
							 filesToFindPersonIndex++;
						 }
					 }
					 if (folderTextbox3->Text->Length != 0)
					 {
						 string thirdFolderName = msclr::interop::marshal_as<std::string>(folderBrowserDialog3->SelectedPath);
						 vector<string> filesToFindPerson3 = FileComputations::getFilesFromFolder(thirdFolderName);
						 filesToFindPersonIndex++;
						 for (int i = 0; i < filesToFindPerson3.size(); i++)
						 {
							 filesToFindPerson.push_back(thirdFolderName + "\\" + filesToFindPerson3[i]);
							 filesToFindPersonIndex++;
						 }
					 }

					 GlobalVariables::setFolderChosen(0);
					 GlobalVariables::setUserImagesToDetectFace(filesToFindPerson);
					 int estimatedTimeInSecs = (filesToFindPerson.size() * 5);
					 String ^ estimatedTimeInMins;
					 if (estimatedTimeInSecs / 60 < 1)
					 {
						 estimatedTimeInMins = "1";
					 }
					 else
					 {
						 estimatedTimeInMins = round(static_cast<float>(estimatedTimeInSecs) / 60).ToString();
					 }
					 loadingLabel->Text = "...this may take approximately " + estimatedTimeInMins + " minute(s)";

					 GlobalVariables::setTabIndex(6);
					 this->tabControl1->SelectedTab = loadingPageTab;
					 loadResultsBackgroundWorker->RunWorkerAsync();
					 progressBarBackgroundWorker->RunWorkerAsync();

					 // loadResultsLV();
					 // GlobalVariables::setTabIndex(5);
					 ////tabIndex = 3;
					 // this->tabControl1->SelectedTab = searchResultstab;

				 }
				 else {
					 MessageBox::Show("Please choose the folder(s) you to to search through to find the person", "Choose Folder", MessageBoxButtons::OK); // if no folder has been chosen this message box appears
				 }
	}

			 // appears as save button located on save profile tab

	private: System::Void chooseProfilebtn_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 // checks if more than one profiles has been selected
				 if (profilesListView->CheckedIndices->Count > 1) {
					 MessageBox::Show("You have picked more than one profile, please choose one", "Selected Profile", MessageBoxButtons::OK);
				 }
				 // checks if a profile has been selected
				 else if (profilesListView->CheckedIndices->Count == 0) {
					 MessageBox::Show("Please select a profile", "Selected Profile", MessageBoxButtons::OK);
				 }
				 else {
					 //SET PROFILE NAME HERE

					 int index = profilesListView->CheckedItems[0]->Index;
					 String^ profileName = profilesListView->Items[index]->Text;
					 int profileId = index + GlobalVariables::getreservedIDs();
					 GlobalVariables::setProfileID(profileId);
					 GlobalVariables::setProfileName(msclr::interop::marshal_as<string>(profileName));
					 GlobalVariables::setTabIndex(4);
					 //tabIndex = 4;
					 this->tabControl1->SelectedTab = searchFoldertab;
				 }
	}

	private: System::Void backToNewProf_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setTabIndex(0);
				 //tabIndex = 0;
				 this->tabControl1->SelectedTab = openMenutab;
	}

	private: System::Void backToOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setTabIndex(0);
				 //tabIndex = 0;
				 this->tabControl1->SelectedTab = openMenutab;

	}

	private: System::Void bckHomebtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setTabIndex(0);
				 //tabIndex = 0;
				 this->tabControl1->SelectedTab = openMenutab;
	}

	private: System::Void btnMoveS_Click(System::Object^  sender, System::EventArgs^  e) {
				 vector<vector<std::string> > detectedFiles = GlobalVariables::getImagesWithProfileFound(); // copy detected images into vector
				 vector<std::string> moveFiles;
				 vector<int> indexOfFiles;
				 for (int i = 0; i < resultsListView->CheckedItems->Count; i++)
				 {
					 //gets index of every checked item (we knw the positions of the elements in the detectedFiles vector matches the index of the list view)
					 int index = resultsListView->CheckedItems[i]->Index;
					 moveFiles.push_back(detectedFiles[index][1]);// copies the file paths of images that have been selected in to moveFiles vector
					 indexOfFiles.push_back(index);
				 }
				 for (int i = indexOfFiles.size() - 1; i >= 0; i--)
				 {
					 // erases file paths of images that have been selected (erases from detectedFiles vector)
					 int index = indexOfFiles[i];
					 detectedFiles.erase(detectedFiles.begin() + index);
				 }
				 ///nathans move file method
				 FileComputations::createFolderAndMove(moveFiles, GlobalVariables::getProfileName());
				 if (detectedFiles.size() == 0)// checks if there are any more files left after user intraction
				 {
					 if (MessageBox::Show("", "No more files, do you want to close Face Finder?", MessageBoxButtons::YesNo,
						 MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
					 {
						 //clearForm();// clears any cached data
						 GlobalVariables::setTabIndex(7);
						 //tabIndex = 5;
						 this->tabControl1->SelectedTab = finishTab;
					 }
					 else
					 {
						 OpeningMenu::Close();// close the whole application
					 }
				 }
				 GlobalVariables::setImagesWithProfileFound(detectedFiles); // sets a new detected files list
				 resultsImagelist->Images->Clear();
				 resultsListView->Clear(); // clear images from the results list view
				 loadResultsLVAfterChange(); // reload the updated list view
	}

			 // appears as unselect radio button on search results tab
	private: System::Void unselectRadioBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (unselectRadioBtn->Checked)
				 {
					 for (int i = 0; i < resultsListView->Items->Count; i++) // unchecks the checkboxes of all items in the results list view
					 {
						 resultsListView->Items[i]->Checked = false;
					 }
				 }
	}

	private: System::Void selectRadioBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (selectRadioBtn->Checked)
				 {
					 for (int i = 0; i < resultsListView->Items->Count; i++) //checks the checkboxes of all items in the results list view
					 {
						 resultsListView->Items[i]->Checked = true;
					 }
				 }
	}

	private: System::Void btnDeleteS_Click(System::Object^  sender, System::EventArgs^  e) { // delete button located on search results tab
				 vector<vector<std::string> > detectedFiles = GlobalVariables::getImagesWithProfileFound();
				 vector<std::string> imagesToDelete;
				 vector<int> indexOfFiles;
				 for (int i = 0; i < resultsListView->CheckedItems->Count; i++)
				 {
					 //gets index of every checked item (we knw the positions of the elements in the detectedFiles vector matches the index of the list view)

					 int index = resultsListView->CheckedItems[i]->Index;
					 imagesToDelete.push_back(detectedFiles[index][1]);// copies the file paths of images that have been selected in to imagesToDelete vector
					 indexOfFiles.push_back(index);

				 }
				 for (int i = indexOfFiles.size() - 1; i >= 0; i--)
				 {
					 int index = indexOfFiles[i];
					 detectedFiles.erase(detectedFiles.begin() + index); // erase alll the files that have been deleted from the detectedFiles vector
				 }

				 ///nathans delete file method (delete the files in the imagesToDelete vector)
				 FileComputations::deleteFiles(imagesToDelete);
				 if (detectedFiles.size() == 0)// checks if there are any more files left after user intraction
				 {
					 if (MessageBox::Show("", "No more files, do you want to close Face Finder?", MessageBoxButtons::YesNo,
						 MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
					 {
						 //clearForm();// clears cached data
						 GlobalVariables::setTabIndex(7);
						 //tabIndex = 5;
						 this->tabControl1->SelectedTab = finishTab;;// go back to the finish tab
					 }
					 else
					 {
						 OpeningMenu::Close(); // close the application
					 }
				 }
				 GlobalVariables::setImagesWithProfileFound(detectedFiles);
				 resultsImagelist->Images->Clear();
				 resultsListView->Clear(); // clear the list view of images
				 loadResultsLVAfterChange(); // reload the listview

	}

			 //-----------------------------------------------------NON-EVENT METHODS----------------------------------------------//

			 // displays the results list view located on the searchResultstab
	public: System::Void loadResultsLV() {

				//THIS SHOULDNT BE HARDCODED FILE PATHS
				//DETECT FACE IN IMAGES AND THEN SEE IF THE PROFILE IS IN THE IMAGES
				int profileId = GlobalVariables::getProfileID();


				//GlobalVariables::setUserImagesWithFaceDetected(imagesWithFacesDetected);
				vector<vector<string> > files = FacialComputations::recognizeFace(GlobalVariables::getUserImagesWithFaceDetected(), profileId);
				GlobalVariables::setImagesWithProfileFound(files);
				if (files.size() > 0) {
					noResultsLabel->Visible = false;
					float progressOfImagesInLV = 1;
					for (unsigned i = 0; i < files.size(); i++)
					{
						//gets the files that have been returned by facial computations and displays them in the list view
						string file = files[i][1]; // gets filepath located at 'i'
						String^ stringFile;
						stringFile = msclr::interop::marshal_as<String^>(file); // converts type "string" to "String^"
						System::Drawing::Image ^ myImage = Image::FromFile(stringFile); // creates a variable of type image and sets it to the image located at the filepath provided
						resultsImagelist->Images->Add(myImage);
						ListViewItem^ lstItem = gcnew ListViewItem(stringFile);
						lstItem->Checked = true; // makes every images' text box checked by default
						lstItem->ImageIndex = i;
						resultsListView->Items->Add(lstItem);
					}
					GlobalVariables::setProgress(105);

				}
				else {
					GlobalVariables::setProgress(105);
					noResultsLabel->Visible = true;
				}
	}

	public: System::Void loadResultsLVAfterChange() {
				vector<vector<string> > files = GlobalVariables::getImagesWithProfileFound();

				if (files.size() > 0) {
					float progressOfImagesInLV = 1;
					for (unsigned i = 0; i < files.size(); i++)
					{
						//gets the files that have been returned by facial computations and displays them in the list view
						string file = files[i][1]; // gets filepath located at 'i'
						String^ stringFile;
						stringFile = msclr::interop::marshal_as<String^>(file); // converts type "string" to "String^"
						System::Drawing::Image ^ myImage = Image::FromFile(stringFile); // creates a variable of type image and sets it to the image located at the filepath provided
						resultsImagelist->Images->Add(myImage);
						ListViewItem^ lstItem = gcnew ListViewItem(stringFile);
						lstItem->Checked = true; // makes every images' text box checked by default
						lstItem->ImageIndex = i;
						resultsListView->Items->Add(lstItem);
					}
				}
				else {

					noResultsLabel->Visible = true;
				}
	}

	public: System::Void loadProfilesLV() {
				string appFolder = FileComputations::getAppDataFolder();
				string thumbnailsFolder = appFolder + "thumbnails\\";
				profilesListView->Scrollable = true;
				profilesImageList = gcnew ImageList;
				profilesImageList->ColorDepth = ColorDepth::Depth32Bit;
				profilesImageList->ImageSize = System::Drawing::Size(65, 65);
				profilesListView->LargeImageList = profilesImageList;
				profilesListView->CheckBoxes = true;
				//std::vector<string> files = FileComputations::getFilesFromFolder("C:\\Users\\Nathan\\Documents\\Visual Studio 2015\\Projects\\Recognize\\Recognize\\thumbnails");
				std::vector<string> files = FileComputations::getFilesFromFolder(thumbnailsFolder);
				//std::vector<string> files = { "thumbnails\\1.jpg", "thumbnails\\2.jpg", "thumbnails\\3.jpg" };
				if (files.size() == 0)
					previousProfileImagesLabel->Visible = true;
				else
				{
					for (int i = 0; i < files.size(); i++)
					{
						previousProfileImagesLabel->Visible = false;
						string filePath = files[i];
						filePath = thumbnailsFolder + filePath;
						String^ img; //for file paths
						size_t pos = filePath.find_last_of('\\');
						string fileName = filePath.substr(pos + 1);
						size_t posOfExtension = fileName.find_last_of('.');
						fileName = fileName.substr(0, posOfExtension);
						if (fileName.find('_')){
							size_t posOfUnderscore = fileName.find_first_of('_');
							fileName = fileName.substr(0, posOfUnderscore);
						}
						string profileName = matchThumnailWithProfileName(fileName);
						String^ profileNameString = msclr::interop::marshal_as<String^>(profileName);
						img = msclr::interop::marshal_as<String^>(filePath);
						System::Drawing::Image ^ myImage = Image::FromFile(img);
						profilesImageList->Images->Add(myImage);
						ListViewItem^ lstItem = gcnew ListViewItem(profileNameString);
						lstItem->ImageIndex = i;
						profilesListView->Items->Add(lstItem);
					}
				}

	}

			//Gets the last id used in a file
	private: System::Int32 lastId(string csvFile) {
				 int idint = -1;
				 string filename = csvFile;
				 ifstream fin;
				 fin.open(filename);
				 if (fin.is_open()) {
					 fin.seekg(-1, ios_base::end);                // go to one spot before the EOF (end of file)
					 bool keepLooping = true;
					 while (keepLooping) {
						 char ch;
						 fin.get(ch);                            // Get current byte's data
						 if ((int)fin.tellg() <= 1) {             // If the data was at or before the 0th byte
							 fin.seekg(0);                       // The first line is the last line
							 keepLooping = false;                // So stop there
						 }
						 else if (ch == '\n') {                   // If the data was a newline
							 keepLooping = false;                // Stop at the current position.
						 }
						 else {                                  // If the data was neither a newline nor at the 0 byte
							 fin.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
						 }
					 }
					 string lastLine, filepath, id;
					 getline(fin, lastLine);                      // Read the current line
					 stringstream liness(lastLine);
					 getline(liness, filepath, ';');
					 getline(liness, id);
					 idint = atoi(id.c_str());
					 fin.close();
				 }
				 return idint;
	}

	private: System::Void toCSV(string csvfile, string filename) {
				 int next_id = lastId(csvfile) + 1; // calculate what the next id should be
				 char filechar[1024];
				 strcpy_s(filechar, filename.c_str()); // create a char 'filechar' then copy the filename into it
				 if (checkFileExistence(csvfile)) {// check if the file exists if so find the last id
					 std::ofstream my_file;
					 my_file.open(csvfile, std::ios::app);
					 my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
					 my_file << "\n" << filechar << ";" << next_id;
				 }
				 else {   //if the file does not exist set the id to '0'
					 std::ofstream my_file;
					 my_file.open(csvfile, std::ios::app);
					 my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
					 my_file << filechar << ";" << 0;
				 }
	}

			 // checks if a file exists
	private: System::Boolean checkFileExistence(string file) {
				 std::ifstream my_file(file);
				 if (my_file) {
					 return true;
				 }
				 return false;
	}

			 // save the thumnbail to the thumbnails folder with an id as its filename




			 //Both split methods split a line in a string vector and return both parts
			 //the split in a vector
			 void split(const string &s, char delim, vector<string> &elems) {
				 stringstream ss(s);
				 string item;
				 while (getline(ss, item, delim)) {
					 elems.push_back(item);
				 }
			 }

			 vector<string> split(const string &s, char delim) {
				 vector<string> elems;
				 split(s, delim, elems);
				 return elems;
			 }

			 string matchThumnailWithProfileName(string fileID) {
				 string profileName, line;
				 size_t pos;
				 std::ifstream my_file;
				 string profilesPath = "profiles.txt";
				 string appFolder = FileComputations::getAppDataFolder();
				 profilesPath = appFolder + profilesPath;
				 my_file.open(profilesPath);
				 while (my_file.good()) {
					 getline(my_file, line); // get line from file
					 vector<string> profileNameAndId = split(line, ';');
					 if (profileNameAndId[1] == fileID) {
						 profileName = profileNameAndId[0];
					 }
				 }
				 return profileName;
			 }



			 // clear the form of any saved user data
	private: System::Void clearForm() {
				 String ^ forTextBox = "";
				 String ^ subjectTextBox = "";
				 String ^ saveProfileTextBox = "";
				 std::vector<string> files;
				 GlobalVariables::setProfileImagesToDetectFace(files);
				 folderBrowserDialog1->SelectedPath = ""; // clear the folder browser data
				 GlobalVariables::setFolderChosen(0);
				 refreshSearchFolderTab();// clear textBox on the chooseFoldertab 
	}

	private: System::Void resultsListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void folderTextbox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void chooseFolderBtn2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (folderBrowserDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // opens a folderBroswerDialog1 allows user to choose a folder to search
					 folderTextbox2->Text = folderBrowserDialog2->SelectedPath;
					 //SETS THE GLOBAL VARIABLE THAT STORES THE IMAGES THAT WILL BE SEARCHED THROUGH TO FIND THE PROFILE
					 GlobalVariables::setFolderChosen(1); // tells the rest of the program that a folder has been chosen
					 //get files from folder
					 //this is my code below to get all the image files from the folder.
					 string folderPath = msclr::interop::marshal_as<std::string>(folderBrowserDialog2->SelectedPath);
					 vector<string> filesToFindPerson = FileComputations::getFilesFromFolder(folderPath);
					 for (int i = 0; i < filesToFindPerson.size(); i++) {
						 filesToFindPerson[i] = folderPath + "\\" + filesToFindPerson[i];
					 }
					 GlobalVariables::setUserImagesToDetectFace(filesToFindPerson);
				 }
				 else {
					 //folderChosen = 0;
					 GlobalVariables::setFolderChosen(0); // tells the rest of the program that no folder has been chosen
				 }
	}

	private: System::Void chooseFolderBtn3_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (folderBrowserDialog3->ShowDialog() == System::Windows::Forms::DialogResult::OK) { // opens a folderBroswerDialog1 allows user to choose a folder to search
					 folderTextbox3->Text = folderBrowserDialog3->SelectedPath;
					 //SETS THE GLOBAL VARIABLE THAT STORES THE IMAGES THAT WILL BE SEARCHED THROUGH TO FIND THE PROFILE
					 GlobalVariables::setFolderChosen(1); // tells the rest of the program that a folder has been chosen
					 //get files from folder
					 //this is my code below to get all the image files from the folder.
					 string folderPath = msclr::interop::marshal_as<std::string>(folderBrowserDialog3->SelectedPath);
					 vector<string> filesToFindPerson = FileComputations::getFilesFromFolder(folderPath);
					 for (int i = 0; i < filesToFindPerson.size(); i++) {
						 filesToFindPerson[i] = folderPath + "\\" + filesToFindPerson[i];
					 }
					 GlobalVariables::setUserImagesToDetectFace(filesToFindPerson);
				 }
				 else {
					 //folderChosen = 0;
					 GlobalVariables::setFolderChosen(0); // tells the rest of the program that no folder has been chosen
				 }
	}

	private: System::Void plusBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setNumberOfFolders(GlobalVariables::getNumberOfFolders() + 1);
				 if (GlobalVariables::getNumberOfFolders() == 2)
				 {
					 folderTextbox2->Visible = true;
					 chooseFolderBtn2->Visible = true;
					 plusBtn->Location = Point(309, 215);
				 }
				 else if (GlobalVariables::getNumberOfFolders() == 3)
				 {
					 folderTextbox3->Visible = true;
					 chooseFolderBtn3->Visible = true;
					 plusBtn->Visible = false;
				 }
	}

	private: System::Void profilesListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	public: System::Void toggleSaveProfileControlsVisibility(){
				if (saveProfileTextBox->Visible == false) {
					saveProfileTextBox->Visible = true;
					namePersonLabel->Visible = true;
					toSearchFolderFromSaveprofile->Visible = true;
					toHomeFromSaveprofile->Visible = true;
					textBox1->Visible = true;
					loadingGif->Visible = false;
					loadingGifLabel->Visible = false;
				}
				else
				{
					saveProfileTextBox->Visible = false;
					namePersonLabel->Visible = false;
					toSearchFolderFromSaveprofile->Visible = false;
					toHomeFromSaveprofile->Visible = false;
					textBox1->Visible = false;
					loadingGif->Visible = true;
					loadingGifLabel->Visible = true;
				}
	}

	public: System::Void refreshSearchFolderTab(){
				folderTextbox->Text = "";
				folderTextbox2->Text = "";
				folderTextbox3->Text = "";
				folderTextbox2->Visible = false;
				folderTextbox3->Visible = false;
				chooseFolderBtn2->Visible = false;
				chooseFolderBtn3->Visible = false;
				GlobalVariables::setFolderChosen(0);
				GlobalVariables::setNumberOfFolders(1);
				plusBtn->Visible = true;
				plusBtn->Location = System::Drawing::Point(309, 135);
				progressBar1->Value = 0;

	}
	public: System::Void updateBar()
	{

				progressBar1->Value = GlobalVariables::getProgress();

	}

	private: System::Void loadResultsBackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

				 /*resultsProgressBar^ bar = gcnew resultsProgressBar(round(static_cast<float>(GlobalVariables::getUserImagesToDetectFace().size()) * 0.2));
				 bar->ShowDialog();bar->updateBar();*/
				 FacialComputations::prepareListViewVariables();
				 this->Invoke(gcnew MethodInvoker(this, &OpeningMenu::loadResultsLV));

	}

	private: System::Void progressBarBackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 while (GlobalVariables::getProgress() != 105)
				 {
					 Thread::Sleep(100);
					 this->Invoke(gcnew MethodInvoker(this, &OpeningMenu::updateBar));
				 }
				 GlobalVariables::setProgress(0);
				 this->Invoke(gcnew MethodInvoker(this, &OpeningMenu::changeToSearchResultsTab));
	}

			 void changeToSearchFolderTab(){
				 GlobalVariables::setTabIndex(4);
				 //tabIndex = 3;
				 this->tabControl1->SelectedTab = searchFoldertab;
			 }
			 void changeToSearchResultsTab(){
				 GlobalVariables::setTabIndex(5);
				 //tabIndex = 3;
				 this->tabControl1->SelectedTab = searchResultstab;
			 }

	private: System::Void resultsFinishBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (MessageBox::Show("Have you finished organising your pictures?", "Warning", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::No)
				 {

				 }
				 else
				 {
					 GlobalVariables::setTabIndex(7);
					 //tabIndex = 3;
					 this->tabControl1->SelectedTab = finishTab;

				 }
	}

	private: System::Void resultsBackBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (MessageBox::Show("You will go back to the folder selection page, proceed?", "Warning", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::No)
				 {

				 }
				 else
				 {
					 refreshSearchFolderTab();
					 GlobalVariables::setTabIndex(4);
					 this->tabControl1->SelectedTab = searchFoldertab;
				 }
	}


	private: System::Void toSearchFolderFromSaveprofile_Click(System::Object^  sender, System::EventArgs^  e) {
				 toggleSaveProfileControlsVisibility();
				 saveProfileBackgroundWorker->RunWorkerAsync();
	}
	private: System::Void saveProfileBackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 if (FileComputations::saveProfile(saveProfileTextBox) == true){
					 this->Invoke(gcnew MethodInvoker(this, &OpeningMenu::changeToSearchFolderTab));
				 }
				 this->Invoke(gcnew MethodInvoker(this, &OpeningMenu::toggleSaveProfileControlsVisibility));
	}
	private: System::Void toHomeFromSaveprofile_Click(System::Object^  sender, System::EventArgs^  e) {
				 GlobalVariables::setTabIndex(0); // change the tab to home menu
				 this->tabControl1->SelectedTab = openMenutab;
	}

	private: System::Void finishCloseBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 OpeningMenu::Close();
	}

	private: System::Void finishHomeBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 clearForm();
				 GlobalVariables::setTabIndex(0); // change the tab to home menu
				 this->tabControl1->SelectedTab = openMenutab;
	}

	private: System::Void openMenutab_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void OnPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 //Pen^ pen = gcnew Pen(Color::FromArgb(1, 215, 218, 219));
				 Pen^ pen = gcnew Pen(Color::Black);
				 g->DrawLine(pen, 450, 30, 450, 330);
	}
	private: System::Void saveProfileTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void previousProfileLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	};
}
