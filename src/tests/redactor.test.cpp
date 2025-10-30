#include "document/Document.h"
#include "documentItem/DocumentItem.h"
#include "image/Image.h"
#include "paragraph/Paragraph.h"

#include "gmock/gmock.h"
#include "resource/IResourceManager.h"

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

	void UnmarkForDeletion(const Path& path) override { /* no-op */ }
	void Cleanup() override { /* no-op */ }
	void SaveImagesTo(const Path& path) const override { /* no-op */ }

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