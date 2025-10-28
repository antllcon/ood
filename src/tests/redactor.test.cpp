#include "documentItem/DocumentItem.h"
#include "image/Image.h"
#include "paragraph/Paragraph.h"
#include "gtest/gtest.h"

#include <memory>
#include <string>

class ConstDocumentItem;
class ParagraphTests : public ::testing::Test
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

class ImageTests : public ::testing::Test
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

class DocumentItemTests : public ::testing::Test
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