#include "command/DeleteItemCommand.h"
#include "command/SetTitleCommand.h"
#include "document/Document.h"
#include "documentItem/DocumentItem.h"
#include "image/Image.h"
#include "paragraph/Paragraph.h"
#include "resource/IResourceManager.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <memory>
#include <string>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

class ConstDocumentItem;
class ParagraphTests : public testing::Test
{
};

TEST_F(ParagraphTests, CanBeConstructedWithText)
{
	const std::string text = "Hello, world!";
	Paragraph p(text);

	EXPECT_EQ(p.GetText(), text);
}

TEST_F(ParagraphTests, CanSetNewText)
{
	const std::string initialText = "Initial";
	Paragraph p(initialText);

	const std::string newText = "Set new text";
	p.SetText(newText);

	EXPECT_EQ(p.GetText(), newText);
}

TEST_F(ParagraphTests, CanSetEmptyText)
{
	Paragraph p("Some text");

	p.SetText("");
	EXPECT_TRUE(p.GetText().empty());
}

TEST_F(ParagraphTests, WorksPolymorphicallyThroughInterface)
{
	const std::string text = "Interface test";
	std::unique_ptr<IParagraph> p = std::make_unique<Paragraph>(text);

	ASSERT_NE(p, nullptr);
	EXPECT_EQ(p->GetText(), text);

	const std::string newText = "New interface text";
	p->SetText(newText);
	EXPECT_EQ(p->GetText(), newText);
}

class ImageTests : public testing::Test
{
};

TEST_F(ImageTests, CanBeConstructedWithValidParameters)
{
	const std::string path = "images/img.png";
	const unsigned int width = 300;
	const unsigned int height = 200;

	Image img(path, width, height);

	EXPECT_EQ(img.GetPath(), path);
	EXPECT_EQ(img.GetWidth(), width);
	EXPECT_EQ(img.GetHeight(), height);
}

TEST_F(ImageTests, CanResizeToValidDimensions)
{
	Image img("path.jpg", 100, 100);

	const unsigned int newWidth = 640;
	const unsigned int newHeight = 480;

	img.Resize(newWidth, newHeight);

	EXPECT_EQ(img.GetWidth(), newWidth);
	EXPECT_EQ(img.GetHeight(), newHeight);
}

TEST_F(ImageTests, ResizeDoesNotChangePath)
{
	const std::string path = "invariant.png";
	Image img(path, 100, 100);

	img.Resize(200, 200);

	EXPECT_EQ(img.GetPath(), path);
}

TEST_F(ImageTests, WorksPolymorphicallyThroughInterface)
{
	const std::string path = "poly.gif";
	const unsigned int width = 50;
	const unsigned int height = 50;

	std::unique_ptr<IImage> img = std::make_unique<Image>(path, width, height);

	ASSERT_NE(img, nullptr);
	EXPECT_EQ(img->GetPath(), path);
	EXPECT_EQ(img->GetWidth(), width);
	EXPECT_EQ(img->GetHeight(), height);

	const unsigned int newWidth = 150;
	const unsigned int newHeight = 120;
	img->Resize(newWidth, newHeight);

	EXPECT_EQ(img->GetWidth(), newWidth);
	EXPECT_EQ(img->GetHeight(), newHeight);
}

TEST_F(ImageTests, ConstructorThrowsOnInvalidDimensions)
{
	EXPECT_THROW(Image("path.png", Image::MIN_DIMENSION - 1, 100), std::out_of_range);
	EXPECT_THROW(Image("path.png", Image::MAX_DIMENSION + 1, 100), std::out_of_range);

	EXPECT_THROW(Image("path.png", 100, Image::MIN_DIMENSION - 1), std::out_of_range);
	EXPECT_THROW(Image("path.png", 100, Image::MAX_DIMENSION + 1), std::out_of_range);
}

TEST_F(ImageTests, ResizeThrowsOnInvalidDimensions)
{
	Image img("path.png", 100, 100);

	EXPECT_THROW(img.Resize(Image::MIN_DIMENSION - 1, 100), std::out_of_range);
	EXPECT_THROW(img.Resize(Image::MAX_DIMENSION + 1, 100), std::out_of_range);

	EXPECT_THROW(img.Resize(100, Image::MIN_DIMENSION - 1), std::out_of_range);
	EXPECT_THROW(img.Resize(100, Image::MAX_DIMENSION + 1), std::out_of_range);
}

TEST_F(ImageTests, AllowsBoundaryDimensions)
{
	EXPECT_NO_THROW(Image("min.png", Image::MIN_DIMENSION, Image::MIN_DIMENSION));
	EXPECT_NO_THROW(Image("max.png", Image::MAX_DIMENSION, Image::MAX_DIMENSION));

	Image img("path.png", 100, 100);

	EXPECT_NO_THROW(img.Resize(Image::MIN_DIMENSION, Image::MIN_DIMENSION));
	EXPECT_EQ(img.GetWidth(), Image::MIN_DIMENSION);
	EXPECT_EQ(img.GetHeight(), Image::MIN_DIMENSION);

	EXPECT_NO_THROW(img.Resize(Image::MAX_DIMENSION, Image::MAX_DIMENSION));
	EXPECT_EQ(img.GetWidth(), Image::MAX_DIMENSION);
	EXPECT_EQ(img.GetHeight(), Image::MAX_DIMENSION);
}

class DocumentItemTests : public testing::Test
{
protected:
	std::shared_ptr<IParagraph> m_paragraph = std::make_shared<Paragraph>("Test paragraph");
	std::shared_ptr<IImage> m_image = std::make_shared<Image>("images/test.png", 100, 100);
};

TEST_F(DocumentItemTests, CanHoldParagraph)
{
	DocumentItem item(m_paragraph);

	EXPECT_EQ(item.GetParagraph(), m_paragraph);
	EXPECT_EQ(item.GetImage(), nullptr);
}

TEST_F(DocumentItemTests, CanHoldImage)
{
	DocumentItem item(m_image);

	EXPECT_EQ(item.GetImage(), m_image);
	EXPECT_EQ(item.GetParagraph(), nullptr);
}

TEST_F(DocumentItemTests, CanAccessParagraphAsConst)
{
	const DocumentItem item(m_paragraph);
	const ConstDocumentItem& constItem = item;

	EXPECT_EQ(constItem.GetParagraph(), m_paragraph);
	EXPECT_EQ(constItem.GetImage(), nullptr);
}

TEST_F(DocumentItemTests, CanAccessImageAsConst)
{
	const DocumentItem item(m_image);
	const ConstDocumentItem& constItem = item;

	EXPECT_EQ(constItem.GetImage(), m_image);
	EXPECT_EQ(constItem.GetParagraph(), nullptr);
}

TEST_F(DocumentItemTests, ConstructorThrowsOnNullParagraph)
{
	std::shared_ptr<IParagraph> nullParagraph = nullptr;
	EXPECT_THROW(DocumentItem item(nullParagraph), std::invalid_argument);
}

TEST_F(DocumentItemTests, ConstructorThrowsOnNullImage)
{
	std::shared_ptr<IImage> nullImage = nullptr;
	EXPECT_THROW(DocumentItem item(nullImage), std::invalid_argument);
}

TEST_F(DocumentItemTests, GettersReturnCorrectTypes)
{
	DocumentItem paragraphItem(m_paragraph);
	DocumentItem imageItem(m_image);

	::testing::StaticAssertTypeEq<decltype(paragraphItem.GetParagraph()), std::shared_ptr<IParagraph>>();
	::testing::StaticAssertTypeEq<decltype(imageItem.GetImage()), std::shared_ptr<IImage>>();

	[[maybe_unused]] const auto& constParagraphItem = paragraphItem;
	[[maybe_unused]] const auto& constImageItem = imageItem;

	::testing::StaticAssertTypeEq<decltype(constParagraphItem.GetParagraph()), std::shared_ptr<const IParagraph>>();
	::testing::StaticAssertTypeEq<decltype(constImageItem.GetImage()), std::shared_ptr<const IImage>>();
}

class StubResourceManager : public IResourceManager
{
public:
	StubResourceManager() = default;
	Path CopyImage(const Path& sourcePath) const override
	{
		m_lastCopiedSource = sourcePath;
		return m_pathToReturn;
	}

	void MarkForDeletion(const Path& path) override
	{
		m_markedPaths.insert(path);
	}

	void UnmarkForDeletion(const Path& path) override
	{ /* no-op */
	}
	void Cleanup() override
	{ /* no-op */
	}
	void SaveImagesTo(const Path& path) const override
	{ /* no-op */
	}

	Path m_pathToReturn = "stub/image.png";
	mutable Path m_lastCopiedSource;
	std::set<Path> m_markedPaths;
};

class StubExporter final : public IExportStrategy
{
public:
	mutable bool m_isCalled = false;
	mutable const IDocument* m_exportedDocument = nullptr;
	mutable Path m_lastPath;

	void Export(const IDocument& document, const Path& outputPath) const override
	{
		m_isCalled = true;
		m_exportedDocument = &document;
		m_lastPath = outputPath;
	}
};

class DocumentTests : public testing::Test
{
protected:
	std::shared_ptr<StubResourceManager> m_res = std::make_shared<StubResourceManager>();
	std::unique_ptr<Document> m_doc = std::make_unique<Document>("Initial Title", m_res);
};

TEST_F(DocumentTests, InitialStateIsCorrect)
{
	EXPECT_EQ(m_doc->GetTitle(), "Initial Title");
	EXPECT_EQ(m_doc->GetItemsCount(), 0);
}

TEST_F(DocumentTests, SetTitleWorks)
{
	m_doc->SetTitle("New Title");
	EXPECT_EQ(m_doc->GetTitle(), "New Title");
}

TEST_F(DocumentTests, SetTitleThrowsOnEmpty)
{
	EXPECT_THROW(m_doc->SetTitle(""), std::invalid_argument);
}

TEST_F(DocumentTests, InsertParagraphAppendsToEnd)
{
	auto p1 = m_doc->InsertParagraph("Hello", std::nullopt);
	ASSERT_EQ(m_doc->GetItemsCount(), 1);
	EXPECT_EQ(m_doc->GetItem(0).GetParagraph(), p1);

	auto p2 = m_doc->InsertParagraph("World", std::nullopt);
	ASSERT_EQ(m_doc->GetItemsCount(), 2);
	EXPECT_EQ(m_doc->GetItem(1).GetParagraph(), p2);
}

TEST_F(DocumentTests, InsertParagraphAtPosition)
{
	auto pB = m_doc->InsertParagraph("B", std::nullopt);
	auto pA = m_doc->InsertParagraph("A", 0);

	ASSERT_EQ(m_doc->GetItemsCount(), 2);
	EXPECT_EQ(m_doc->GetItem(0).GetParagraph(), pA);
	EXPECT_EQ(m_doc->GetItem(1).GetParagraph(), pB);
}

TEST_F(DocumentTests, InsertParagraphThrowsOnInvalidPosition)
{
	EXPECT_THROW(m_doc->InsertParagraph("A", 1), std::out_of_range);
}

TEST_F(DocumentTests, InsertImageCallsResourceManager)
{
	m_res->m_pathToReturn = "images/generated_cat.png";
	auto img = m_doc->InsertImage("C:/source/cat.png", 300, 200);

	ASSERT_EQ(m_doc->GetItemsCount(), 1);
	EXPECT_EQ(m_doc->GetItem(0).GetImage(), img);
	EXPECT_EQ(img->GetWidth(), 300);

	EXPECT_EQ(m_res->m_lastCopiedSource, "C:/source/cat.png");
	EXPECT_EQ(img->GetPath(), "images/generated_cat.png");
}

TEST_F(DocumentTests, GetItemAndConstGetItemWork)
{
	m_doc->InsertParagraph("Test");

	m_doc->GetItem(0).GetParagraph()->SetText("Mutated");
	EXPECT_EQ(m_doc->GetItem(0).GetParagraph()->GetText(), "Mutated");

	const IDocument& constDoc = *m_doc;
	const ConstDocumentItem& constItem = constDoc.GetItem(0);
	EXPECT_EQ(constItem.GetParagraph()->GetText(), "Mutated");

	// Эта строка не скомпилируется
	// constItem.GetParagraph()->SetText("Won't compile");
}

TEST_F(DocumentTests, DeleteItemRemovesItem)
{
	m_doc->InsertParagraph("A", std::nullopt);
	m_doc->InsertParagraph("B", std::nullopt);
	m_doc->InsertParagraph("C", std::nullopt);

	m_doc->DeleteItem(1); // Удаляем "B"

	ASSERT_EQ(m_doc->GetItemsCount(), 2);
	EXPECT_EQ(m_doc->GetItem(0).GetParagraph()->GetText(), "A");
	EXPECT_EQ(m_doc->GetItem(1).GetParagraph()->GetText(), "C");
}

TEST_F(DocumentTests, TDD_DeleteItemMarksImageForDeletion)
{
	m_res->m_pathToReturn = "img.png";
	auto img = m_doc->InsertImage("source.png", 100, 100);
	Path imagePath = img->GetPath();

	m_doc->DeleteItem(0);

	bool isMarked = m_res->m_markedPaths.contains(imagePath);
	ASSERT_TRUE(isMarked) << "DeleteItem не вызвал MarkForDeletion у ResourceManager!";
}

TEST_F(DocumentTests, SaveDelegatesToStrategy)
{
	StubExporter exporter;
	Path savePath = "C:/my-doc.html";

	m_doc->Save(savePath, exporter);

	EXPECT_TRUE(exporter.m_isCalled);
	EXPECT_EQ(exporter.m_lastPath, savePath);
	EXPECT_EQ(exporter.m_exportedDocument, m_doc.get());
}

class MockCommand : public ICommand
{
public:
	MOCK_METHOD(void, DoExecute, (), (override));
	MOCK_METHOD(void, DoUnexecute, (), (override));
	MOCK_METHOD(bool, TryToMerge, (const ICommand&), (override));

	MOCK_METHOD(void, Die, ());
	~MockCommand() override
	{
		Die();
	}
};

using testing::InSequence;

class CommandHistoryTests : public testing::Test
{
public:
	// Создаем уникальные указатели на моки
	// CommandHistory будет забирать владение ими
	std::unique_ptr<StrictMock<MockCommand>> CreateMock()
	{
		// Мы должны хранить "сырой" указатель, чтобы проверять ожидания (EXPECT_CALL)
		// после того, как unique_ptr был перемещен (moved) в историю
		auto rawPtr = new StrictMock<MockCommand>();
		m_rawMocks.push_back(rawPtr); // Сохраняем для проверок

		// По умолчанию, слияние не удалось
		EXPECT_CALL(*rawPtr, TryToMerge(_)).WillRepeatedly(Return(false));

		return std::unique_ptr<StrictMock<MockCommand>>(rawPtr);
	}

protected:
	CommandHistory m_history;
	// Храним сырые указатели, т.к. unique_ptr будут переданы в m_history
	std::vector<StrictMock<MockCommand>*> m_rawMocks;
};

// --- Тест 1: Начальное состояние ---
TEST_F(CommandHistoryTests, InitialState)
{
	EXPECT_FALSE(m_history.CanUndo());
	EXPECT_FALSE(m_history.CanRedo());

	// Вызовы на пустой истории не должны падать
	EXPECT_NO_THROW(m_history.Undo());
	EXPECT_NO_THROW(m_history.Redo());
}

// --- Тест 2: Добавление и выполнение команды ---
TEST_F(CommandHistoryTests, AddAndExecuteCommand)
{
	auto cmd = CreateMock();

	// Ожидаем, что команда будет ВЫПОЛНЕНА при добавлении
	EXPECT_CALL(*cmd, DoExecute()).Times(1);

	m_history.AddAndExecuteCommand(std::move(cmd));

	EXPECT_TRUE(m_history.CanUndo());
	EXPECT_FALSE(m_history.CanRedo());
}

// --- Тест 3: Полный цикл Undo/Redo ---
TEST_F(CommandHistoryTests, UndoAndRedoCycle)
{
	auto cmd = CreateMock();

	// InSequence гарантирует, что вызовы произойдут в этом порядке
	{
		InSequence seq;

		// 1. Добавление
		EXPECT_CALL(*cmd, DoExecute());
		// 2. Отмена
		EXPECT_CALL(*cmd, DoUnexecute());
		// 3. Повтор
		EXPECT_CALL(*cmd, DoExecute());
	}

	// 1. Добавление
	m_history.AddAndExecuteCommand(std::move(cmd));
	ASSERT_TRUE(m_history.CanUndo());
	ASSERT_FALSE(m_history.CanRedo());

	// 2. Отмена
	m_history.Undo();
	ASSERT_FALSE(m_history.CanUndo());
	ASSERT_TRUE(m_history.CanRedo());

	// 3. Повтор
	m_history.Redo();
	ASSERT_TRUE(m_history.CanUndo());
	ASSERT_FALSE(m_history.CanRedo());
}

// --- Тест 4: Добавление новой команды очищает Redo Stack (Критический тест!) ---
// Это проверяет правило: "удаление отмененной команды 5... должно удалять файл"
TEST_F(CommandHistoryTests, AddCommandClearsRedoStackAndDestroysCommands)
{
	auto cmd1 = CreateMock();
	auto cmd2 = CreateMock();
	auto cmd3 = CreateMock(); // Новая команда

	// 1. Добавляем две команды
	EXPECT_CALL(*cmd1, DoExecute());
	m_history.AddAndExecuteCommand(std::move(cmd1));

	EXPECT_CALL(*cmd2, DoExecute());
	m_history.AddAndExecuteCommand(std::move(cmd2));

	// 2. Отменяем их обе (cmd2, потом cmd1)
	EXPECT_CALL(*cmd2, DoUnexecute());
	m_history.Undo();

	EXPECT_CALL(*cmd1, DoUnexecute());
	m_history.Undo();

	ASSERT_FALSE(m_history.CanUndo());
	ASSERT_TRUE(m_history.CanRedo()); // cmd1 и cmd2 в стеке Redo

	// 3. Добавляем новую команду (cmd3)
	// Это должно УНИЧТОЖИТЬ cmd1 и cmd2 (и их ресурсы)
	{
		InSequence seq;

		// "удаление отмененной команды... должно физически удалять ресурс"
		// Мы ожидаем вызов деструкторов В ОБРАТНОМ ПОРЯДКЕ (LIFO)
		EXPECT_CALL(*cmd2, Die()); // Сначала удаляется cmd2
		EXPECT_CALL(*cmd1, Die()); // Потом удаляется cmd1

		// И только потом выполняется новая команда
		EXPECT_CALL(*cmd3, DoExecute());
	}

	m_history.AddAndExecuteCommand(std::move(cmd3));

	// 4. Проверяем состояние
	EXPECT_TRUE(m_history.CanUndo());  // Только cmd3 доступна для отмены
	EXPECT_FALSE(m_history.CanRedo()); // cmd1 и cmd2 стерты
}

// --- Тест 5: Проверка лимита истории (10 команд) (Критический тест!) ---
// Это проверяет правило: "удаление выполненного действия должно физически удалять ресурс"
TEST_F(CommandHistoryTests, HistoryLimitIs10)
{
	InSequence seq; // Порядок важен

	// 1. Заполняем историю 10 командами
	std::vector<std::unique_ptr<StrictMock<MockCommand>>> commands;
	for (int i = 0; i < 10; ++i)
	{
		commands.push_back(CreateMock());
		// Ожидаем Execute для каждой
		EXPECT_CALL(*m_rawMocks[i], DoExecute());
		m_history.AddAndExecuteCommand(std::move(commands.back()));
	}

	ASSERT_EQ(m_rawMocks.size(), 10);
	ASSERT_TRUE(m_history.CanUndo());

	// 2. Добавляем 11-ю команду
	auto cmd11 = CreateMock();

	// ОЖИДАЕМ, что САМАЯ СТАРАЯ (cmd 0) будет УНИЧТОЖЕНА
	// "удаление выполненного действия должно физически удалять ресурс"
	EXPECT_CALL(*m_rawMocks[0], Die());

	// И 11-я будет выполнена
	EXPECT_CALL(*cmd11, DoExecute());

	m_history.AddAndExecuteCommand(std::move(cmd11));

	// 3. Проверяем состояние
	EXPECT_TRUE(m_history.CanUndo()); // Все еще можем отменять
	EXPECT_FALSE(m_history.CanRedo());

	// 4. Убедимся, что cmd 0 действительно удалена
	// Отменяем все 10 команд из истории
	for (int i = 10; i >= 1; --i) // От m_rawMocks[10] (cmd11) до m_rawMocks[1]
	{
		EXPECT_CALL(*m_rawMocks[i], DoUnexecute());
		m_history.Undo();
	}

	// m_rawMocks[0] (cmd 0) не должна быть вызвана, т.к. ее нет в истории

	ASSERT_FALSE(m_history.CanUndo()); // История Undo пуста
	ASSERT_TRUE(m_history.CanRedo());  // Вся история (10) теперь в Redo
}

class SetTitleCommandTests : public testing::Test
{
protected:
	// "Жертва": Это строка m_title, которая якобы живет в Document
	std::string m_targetTitle = "Initial Title";
};

TEST_F(SetTitleCommandTests, ExecuteChangesString)
{
	const std::string newTitle = "New Title";
	SetTitleCommand cmd(m_targetTitle, newTitle);

	cmd.Execute();

	EXPECT_EQ(m_targetTitle, newTitle);
}

TEST_F(SetTitleCommandTests, UnexecuteRestoresString)
{
	const std::string newTitle = "New Title";
	SetTitleCommand cmd(m_targetTitle, newTitle);

	cmd.Execute();	 // m_targetTitle = "New Title"
	cmd.Unexecute(); // m_targetTitle = "Initial Title"

	EXPECT_EQ(m_targetTitle, "Initial Title");
}

TEST_F(SetTitleCommandTests, RedoWorksCorrectly)
{
	const std::string newTitle = "New Title";
	SetTitleCommand cmd(m_targetTitle, newTitle);

	cmd.Execute();	 // Initial -> New
	cmd.Unexecute(); // New -> Initial
	cmd.Execute();	 // Initial -> New

	EXPECT_EQ(m_targetTitle, newTitle);
}

// --- "Вау"-тесты на склеивание (Merging) ---

TEST_F(SetTitleCommandTests, TryToMergeSucceedsWithAnotherSetTitleCommand)
{
	SetTitleCommand cmd1(m_targetTitle, "Title 1");

	const std::string finalTitle = "Title 2";
	SetTitleCommand cmd2(m_targetTitle, finalTitle);

	// TDD: Проверяем, что cmd1 "поглощает" cmd2
	EXPECT_TRUE(cmd1.TryToMerge(cmd2));

	// Теперь cmd1 должна содержать m_newTitle из cmd2
	// (m_oldTitle у cmd1 должен остаться старым)
	cmd1.Execute(); // Initial -> Title 2
	EXPECT_EQ(m_targetTitle, finalTitle);

	cmd1.Unexecute(); // Title 2 -> Initial
	EXPECT_EQ(m_targetTitle, "Initial Title");
}

TEST_F(SetTitleCommandTests, TryToMergeFailsWithDifferentCommandType)
{
	SetTitleCommand cmd(m_targetTitle, "New Title");

	// Используем MockCommand, чтобы имитировать другую команду
	StrictMock<MockCommand> otherCmd;
	EXPECT_CALL(otherCmd, TryToMerge(_)).WillRepeatedly(Return(false));

	// TDD: Слияние не должно произойти
	EXPECT_FALSE(cmd.TryToMerge(otherCmd));
}

// Используем StubResourceManager, который УЖЕ ОПРЕДЕЛЕН в твоем файле
class DeleteItemCommandTests : public testing::Test
{
protected:
	void SetUp() override
	{
		m_res = std::make_shared<StubResourceManager>();

		// Создаем "документ" (просто вектор)
		m_items.emplace_back(std::make_shared<Paragraph>("Paragraph 1"));

		// Создаем изображение и путь
		m_imagePath = "images/img_to_delete.png";
		m_res->m_pathToReturn = m_imagePath; // Настраиваем заглушку
		m_image = std::make_shared<Image>(m_imagePath, 1, 1);

		m_items.emplace_back(m_image); // [Paragraph, Image]
	}

	std::shared_ptr<StubResourceManager> m_res;
	std::vector<DocumentItem> m_items;
	std::shared_ptr<IImage> m_image;
	Path m_imagePath;
};

TEST_F(DeleteItemCommandTests, ExecuteMarksImageForDeletion)
{
	// Команда на удаление m_items[1] (Изображение)
	DeleteItemCommand cmd(m_items, m_res, 1);

	cmd.Execute();

	// Проверяем, что элемент удален из вектора
	ASSERT_EQ(m_items.size(), 1);

	// Проверяем, что RM был вызван
	bool isMarked = m_res->m_markedPaths.contains(m_imagePath);
	EXPECT_TRUE(isMarked);
}

TEST_F(DeleteItemCommandTests, ExecuteDoesNotMarkParagraph)
{
	// Команда на удаление m_items[0] (Параграф)
	DeleteItemCommand cmd(m_items, m_res, 0);

	cmd.Execute();

	ASSERT_EQ(m_items.size(), 1);

	// Проверяем, что RM НЕ был вызван
	bool isMarked = m_res->m_markedPaths.contains(m_imagePath);
	EXPECT_FALSE(isMarked);
}

TEST_F(DeleteItemCommandTests, UnexecuteRestoresItemAndUnmarksResource)
{
	DeleteItemCommand cmd(m_items, m_res, 1); // Удаляем Image

	// 1. Выполняем (удаляет 'Image', помечает 'img.png')
	cmd.Execute();
	ASSERT_EQ(m_items.size(), 1);
	ASSERT_TRUE(m_res->m_markedPaths.contains(m_imagePath));

	// 2. Отменяем
	cmd.Unexecute();

	// Проверяем, что элемент вернулся
	ASSERT_EQ(m_items.size(), 2);
	EXPECT_EQ(m_items[1].GetImage(), m_image);

	// Проверяем, что пометка с ресурса снята
	bool isMarked = m_res->m_markedPaths.contains(m_imagePath);
	EXPECT_FALSE(isMarked);
}

