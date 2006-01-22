using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Collections;
using Iesi.Collections;
using NRSS.mapping;

namespace NRSS.Screensaver.UI
{
  /// <summary>
  /// Encapsulates the rendering of a list of feeds.  Each feed's description is shown in a list, and a single feed is selected.
  /// </summary>
  /// <typeparam name="T">The type of feed that this FeedListView will draw.</typeparam>
  public class FeedListView : IDisposable
  {
    private const float percentOfArticleDisplayBoxToFillWithText = 0.5f;
    private const float percentOfFontHeightForSelectionBox = 1.5f;
    private const int padding = 20;

    // Where to draw
    private Point location;
    private Size size;

    private string title;
    private Font feedFont;
    private Font titleFont;
    private Color backColor;
    private Color borderColor;
    private Color foreColor;
    private Color titleBackColor;
    private Color titleForeColor;
    private Color selectedForeColor;
    private Color selectedBackColor;
    private float feedFontHeight;
    // An index of the currently selected feed
    private int selectedIndex;
    // The list of feeds to draw
    private IList feeds;
    // The maximum number of articles that will be displayed
    private int maxFeedsToShow;
    // The minimum number of articles that will be displayed
    // If there are less feeds than this in the RSS feednel
    // then there will be blank space in the display
    private int minFeedsToShow;

    private int NumArticles { get { return Math.Min(feeds.Count, maxFeedsToShow); } }
    private int NumArticleRows { get { return Math.Max(NumArticles, minFeedsToShow); } }

    public Point Location { get { return location; } set { location = value; } }
    public Size Size { get { return size; } set { size = value; } }

    public Color ForeColor { get { return foreColor; } set { foreColor = value; } }
    public Color BackColor { get { return backColor; } set { backColor = value; } }
    public Color BorderColor { get { return borderColor; } set { borderColor = value; } }
    public Color TitleForeColor { get { return titleForeColor; } set { titleForeColor = value; } }
    public Color TitleBackColor { get { return titleBackColor; } set { titleBackColor = value; } }
    public Color SelectedForeColor { get { return selectedForeColor; } set { selectedForeColor = value; } }
    public Color SelectedBackColor { get { return selectedBackColor; } set { selectedBackColor = value; } }
    public int MaxFeedsToShow { get { return maxFeedsToShow; } set { maxFeedsToShow = value; } }
    public int MinFeedsToShow { get { return minFeedsToShow; } set { minFeedsToShow = value; } }
    public int SelectedIndex { get { return selectedIndex; } }
    public int numFeeds { get { return feeds.Count; } }
    public Feed SelectedFeed { get { return feeds[selectedIndex] as Feed; } }

    public int RowHeight
    {
      get
      {
        // There is one row for each feed plus 2 rows for the title.
        return size.Height / (NumArticleRows + 2);
      }
    }

    public Font FeedFont
    {
      get
      {
        // Choose a font for each of the feed titles that will fit all numfeeds 
        // of them (plus some slack for the title) in the control 
        feedFontHeight = (float)(percentOfArticleDisplayBoxToFillWithText * RowHeight);
        if (feedFont == null || feedFont.Size != feedFontHeight)
        {
          feedFont = new Font("Microsoft Sans Serif", feedFontHeight, GraphicsUnit.Pixel);
        }
        return feedFont;
      }
    }

    public Font TitleFont
    {
      get
      {
        // Choose a font for the title text.
        // This font will be twice as big as the FeedFont
        float titleFontHeight = (float)(percentOfArticleDisplayBoxToFillWithText * 2 * RowHeight);
        if (titleFont == null || titleFont.Size != titleFontHeight)
        {
          titleFont = new Font("Microsoft Sans Serif", titleFontHeight, GraphicsUnit.Pixel);
        }
        return titleFont;
      }
    }

    public void NextArticle()
    {
      if (SelectedIndex < feeds.Count - 1)
        selectedIndex++;
      else
        selectedIndex = 0;
    }

    public void PreviousArticle()
    {
      if (SelectedIndex > 0)
        selectedIndex--;
      else
        selectedIndex = feeds.Count - 1;
    }

    public FeedListView(string title, IList feeds)
    {
      if (feeds == null)
        throw new ArgumentException("feeds cannot be null", "feeds");

      this.feeds = feeds;
      this.title = title;
    }

    public void Paint(PaintEventArgs args)
    {
      Graphics g = args.Graphics;

      // Settings to make the text drawing look nice
      g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
      g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

      DrawBackground(g);

      // Draw each article's description
      for (int index = 0; index < feeds.Count && index < maxFeedsToShow; index++)
      {
        DrawFeedTitle(g, index);
      }

      // Draw the title text
      DrawTitle(g);
    }

    /// <summary>
    /// Draws a box and border ontop of which the text of the feeds can be drawn.
    /// </summary>
    /// <param name="g">The Graphics object to draw onto</param>
    private void DrawBackground(Graphics g)
    {
      using (Brush backBrush = new SolidBrush(BackColor))
      using (Pen borderPen = new Pen(BorderColor, 4))
      {
        g.FillRectangle(backBrush, new Rectangle(Location.X + 4, Location.Y + 4, Size.Width - 8, Size.Height - 8));
        g.DrawRectangle(borderPen, new Rectangle(Location, Size));
      }
    }

    /// <summary>
    /// Draws the title of the feed with the given index.
    /// </summary>
    /// <param name="g">The Graphics object to draw onto</param>
    /// <param name="index">The index of the feed in the list</param>
    private void DrawFeedTitle(Graphics g, int index)
    {
      // Set formatting and layout
      StringFormat stringFormat = new StringFormat(StringFormatFlags.LineLimit);
      stringFormat.Trimming = StringTrimming.EllipsisCharacter;
      Rectangle articleRect = new Rectangle(Location.X + padding, Location.Y + (int)(index * RowHeight) + padding, Size.Width - (2 * padding), (int)(percentOfFontHeightForSelectionBox * feedFontHeight));

      // Select color and draw border if current index is selected
      Color textBrushColor = ForeColor;
      if ((SelectedIndex >= MaxFeedsToShow ? (index + SelectedIndex - MaxFeedsToShow + 1) : index) == SelectedIndex)
      {
        textBrushColor = SelectedForeColor;
        using (Brush backBrush = new SolidBrush(SelectedBackColor))
        {
          g.FillRectangle(backBrush, articleRect);
        }
      }

      // Draw the title of the feed
      string textToDraw = (feeds[SelectedIndex >= MaxFeedsToShow ? (index + SelectedIndex - MaxFeedsToShow + 1) : index] as Feed).Name;
      using (Brush textBrush = new SolidBrush(textBrushColor))
      {
        g.DrawString(textToDraw, FeedFont, textBrush, articleRect, stringFormat);
      }
    }

    /// <summary>
    /// Draws a title bar.
    /// </summary>
    /// <param name="g">The Graphics object to draw onto</param>
    private void DrawTitle(Graphics g)
    {
      Point titleLocation = new Point(Location.X + padding, Location.Y + Size.Height - (RowHeight) - (padding / 2));
      Size titleSize = new Size(Size.Width - (2 * padding), 2 * RowHeight);
      Rectangle titleRectangle = new Rectangle(titleLocation, titleSize);

      // Draw the title box and the selected feed box
      using (Brush titleBackBrush = new SolidBrush(TitleBackColor))
      {
        g.FillRectangle(titleBackBrush, titleRectangle);
      }

      // Draw the title text
      StringFormat titleFormat = new StringFormat(StringFormatFlags.LineLimit);
      titleFormat.Alignment = StringAlignment.Far;
      titleFormat.Trimming = StringTrimming.EllipsisCharacter;
      using (Brush titleBrush = new SolidBrush(TitleForeColor))
      {
        g.DrawString(title, TitleFont, titleBrush, titleRectangle, titleFormat);
      }
    }

    /// <summary>
    /// Dispose all disposable fields
    /// </summary>
    public void Dispose()
    {
      if (feedFont != null)
        feedFont.Dispose();
      if (titleFont != null)
        titleFont.Dispose();
    }

  }
}
