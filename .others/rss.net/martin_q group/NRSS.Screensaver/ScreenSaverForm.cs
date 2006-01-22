using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Collections;
using Iesi.Collections;
using System.Windows.Forms;
using NRSS.mapping;
using NRSS.Screensaver.UI;
using NRSS.Screensaver.Rss;

namespace NRSS.Screensaver
{
  partial class ScreenSaverForm : Form
  {
    // The RssFeed to display articles from
    private IList feedList;
    private IList itemList;
    private Feed rssFeed;
    private Feed rssFeed1;
    private Feed rssFeed2;
    private Feed rssFeed3;
    private Feed rssFeed4;
    private Feed rssFeed5;
    private Feed rssFeed6;
    private Feed rssFeed7;
    private Feed rssFeed8;
    private Feed rssFeed9;
    private Feed rssFeed10;

    private ItemListView rssView;
    private ItemDescriptionView<Item> rssDescriptionView;
    private FeedListView feedView;
    // The images to display in the background
    private List<Image> backgroundImages;
    private int currentImageIndex;

    // Keep track of whether the screensaver has become active.
    private bool isActive = false;

    // Keep track of the location of the mouse
    private Point mouseLocation;
    private Service serv;

    private List<string> imageExtensions = new List<string>(new string[] { "*.bmp", "*.gif", "*.png", "*.jpg", "*.jpeg" });

    public ScreenSaverForm()
    {
      serv = new Service();
      InitializeComponent();

      SetupScreenSaver();
      LoadBackgroundImage();
      LoadRssFeeds();

      feedView = new FeedListView("NRSS feeds", feedList);
      InitializeFeedView();

      itemList = new ArrayList();
      foreach (Chan tempChan in feedView.SelectedFeed.Chans)
        foreach (Item tempItem in tempChan.Items)
          itemList.Add(tempItem);
      rssView = new ItemListView("NRSS messages", itemList);
      InitializeRssView();

      rssDescriptionView = new ItemDescriptionView<Item>();
      InitializeRssDescriptionView();
    }


    /// <summary>
    /// Set up the main form as a full screen screensaver.
    /// </summary>
    private void SetupScreenSaver()
    {
      // Use double buffering to improve drawing performance
      this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint, true);
      // Capture the mouse
      this.Capture = true;

      // Set the application to full screen mode and hide the mouse
      Cursor.Hide();
      Bounds = Screen.PrimaryScreen.Bounds;
      WindowState = FormWindowState.Maximized;
      ShowInTaskbar = false;
      DoubleBuffered = true;
      BackgroundImageLayout = ImageLayout.Stretch;
    }

    private void LoadBackgroundImage()
    {
      // Initialize the background images.
      backgroundImages = new List<Image>();
      currentImageIndex = 0;

      if (Directory.Exists(Properties.Settings.Default.BackgroundImagePath))
      {
        try
        {
          // Try to load the images given by the users.
          LoadImagesFromFolder();
        }
        catch
        {
          // If this fails, load the default images.
          LoadDefaultBackgroundImages();
        }
      }

      // If no images were loaded, load the defaults
      if (backgroundImages.Count == 0)
      {
        LoadDefaultBackgroundImages();
      }
    }

    private void LoadImagesFromFolder()
    {
      DirectoryInfo backgroundImageDir = new DirectoryInfo(Properties.Settings.Default.BackgroundImagePath);
      // For each image extension (.jpg, .bmp, etc.)
      foreach (string imageExtension in imageExtensions)
      {
        // For each file in the directory provided by the user
        foreach (FileInfo file in backgroundImageDir.GetFiles(imageExtension))
        {
          // Try to load the image
          try
          {
            Image image = Image.FromFile(file.FullName);
            backgroundImages.Add(image);
          }
          catch (OutOfMemoryException)
          {
            // If the image can't be loaded, move on.
            continue;
          }
        }
      }
    }


    private void LoadDefaultBackgroundImages()
    {
      // If the background images could not be loaded for any reason
      // use the image stored in the resources 
      backgroundImages.Add(Properties.Resources.Blue_Light_by_Infinite705);
    }

    private void LoadRssFeeds()
    {
      /*try
      {
        // Try to get it from the users settings
        rssFeed = RssFeed.FromUri(Properties.Settings.Default.RssFeedUri);
      }
      catch
      {
        // If there is any problem loading the RSS load an error message RSS feed
        rssFeed = RssFeed.FromText(Properties.Resources.DefaultRSSText);
        //rssFeed = RssFeed.FromText(serv.HelloWorld());
      }*/

      feedList = new ArrayList();
      rssFeed = new Feed();
      rssFeed.Chans = new HashedSet();
      rssFeed.Chans.Clear();

      for (int i = 0; i < 3; i++)
      {
        Chan chan = new Chan();

        chan.Feed = rssFeed;
        rssFeed.Name = "NRSS Feed";

        chan.Title = "Chan number ";
        chan.Title += i;
        chan.Description = "Here is a really precise description";

        chan.Items = new ArrayList();
        chan.Items.Clear();

        for (int j = 0; j < 1 * (i + 1); j++)
        {
          Item item = new Item();

          item.Chan = chan;

          item.Author = "Me";
          item.Date = DateTime.Now;
          item.Title = "Message number ";
          item.Title += j;
          item.Description = "No offense, but you just won't be reading any useful information. You'd better check this site: www.google.fr";
          item.Link = new Uri("http://www.perdu.com");

          chan.Items.Add(item);
        }

        rssFeed.Chans.Add(chan);
        rssFeed1 = new Feed();
        rssFeed1.Chans = rssFeed.Chans;
        rssFeed1.Name = "Another feed";
        rssFeed2 = new Feed();
        rssFeed2.Chans = rssFeed.Chans;
        rssFeed2.Name = "Not the same feed";
        rssFeed3 = new Feed();
        rssFeed3.Chans = rssFeed.Chans;
        rssFeed3.Name = "A feed again";
        rssFeed4 = new Feed();
        rssFeed4.Chans = rssFeed.Chans;
        rssFeed4.Name = "Still a feed";
        rssFeed5 = new Feed();
        rssFeed5.Chans = rssFeed.Chans;
        rssFeed5.Name = "Guess what ? a feed !";
        rssFeed6 = new Feed();
        rssFeed6.Chans = rssFeed.Chans;
        rssFeed6.Name = "Once again a feed";
        rssFeed7 = new Feed();
        rssFeed7.Chans = rssFeed.Chans;
        rssFeed7.Name = "Some other feed";
        rssFeed8 = new Feed();
        rssFeed8.Chans = rssFeed.Chans;
        rssFeed8.Name = "Not an important feed";
        rssFeed9 = new Feed();
        rssFeed9.Chans = rssFeed.Chans;
        rssFeed9.Name = "One more feed";
        rssFeed10 = new Feed();
        rssFeed10.Chans = rssFeed.Chans;
        rssFeed10.Name = "Last feed";
      }
      feedList.Add(rssFeed);
      feedList.Add(rssFeed1);
      feedList.Add(rssFeed2);
      feedList.Add(rssFeed3);
      feedList.Add(rssFeed4);
      feedList.Add(rssFeed5);
      feedList.Add(rssFeed6);
      feedList.Add(rssFeed7);
      feedList.Add(rssFeed8);
      feedList.Add(rssFeed9);
      feedList.Add(rssFeed10);
    }

    /// <summary>
    /// Initialize display properties of the rssView.
    /// </summary>
    private void InitializeRssView()
    {
      rssView.BackColor = Color.AliceBlue;
      rssView.BorderColor = Color.White;
      rssView.ForeColor = Color.SteelBlue;
      rssView.SelectedBackColor = Color.SteelBlue;
      rssView.SelectedForeColor = Color.AliceBlue;
      rssView.TitleBackColor = Color.Empty;
      rssView.TitleForeColor = Color.Navy;
      rssView.MaxItemsToShow = 20;
      rssView.MinItemsToShow = 1;
      rssView.Location = new Point(Width / 10, Height / 10);
      rssView.Size = new Size(Width / 2, Height / 2);
    }

    /// <summary>
    /// Initialize display properties of the rssDescriptionView.
    /// </summary>
    private void InitializeRssDescriptionView()
    {
      rssDescriptionView.DisplayItem = rssView.SelectedItem;
      rssDescriptionView.ForeColor = Color.Navy;
      rssDescriptionView.TitleFont = rssView.TitleFont;
      rssDescriptionView.TitleFont = new Font("Microsoft Sans Serif", 30, GraphicsUnit.Pixel);
      rssDescriptionView.LineColor = Color.Navy;
      rssDescriptionView.LineWidth = 2f;
      rssDescriptionView.FadeTimer.Tick += new EventHandler(FadeTimer_Tick);
      rssDescriptionView.FadeTimer.Interval = 1;
      rssDescriptionView.Location = new Point(3 * Width / 4, Height / 10);
      rssDescriptionView.Size = new Size(Width / 4, 4 * Height / 5);
      rssDescriptionView.FadingComplete += new EventHandler(rssItemView_FadingComplete);
    }

    private void InitializeFeedView()
    {
      feedView.BackColor = Color.AliceBlue;
      feedView.BorderColor = Color.White;
      feedView.ForeColor = Color.SteelBlue;
      feedView.SelectedBackColor = Color.SteelBlue;
      feedView.SelectedForeColor = Color.AliceBlue;
      feedView.TitleBackColor = Color.Empty;
      feedView.TitleForeColor = Color.Navy;
      feedView.MaxFeedsToShow = 10;
      feedView.MinFeedsToShow = 1;
      feedView.Location = new Point(Width / 10, 7 * Height / 10);
      feedView.Size = new Size(Width / 2, Height / 4);
    }


    private void ScreenSaverForm_MouseMove(object sender, MouseEventArgs e)
    {
      // Set IsActive and MouseLocation only the first time this event is called.
      if (!isActive)
      {
        mouseLocation = MousePosition;
        isActive = true;
      }
      else
      {
        // If the mouse has moved significantly since first call, close.
        if ((Math.Abs(MousePosition.X - mouseLocation.X) > 10) ||
            (Math.Abs(MousePosition.Y - mouseLocation.Y) > 10))
        {
          Close();
        }
      }
    }

    private void ScreenSaverForm_KeyDown(object sender, KeyEventArgs e)
    {
      Close();

    }

    private void ScreenSaverForm_MouseDown(object sender, MouseEventArgs e)
    {
      Close();
    }

    protected override void OnPaintBackground(PaintEventArgs e)
    {
      // Draw the current background image stretched to fill the full screen
      e.Graphics.DrawImage(backgroundImages[currentImageIndex], 0, 0, Size.Width, Size.Height);
    }

    protected override void OnPaint(PaintEventArgs e)
    {
      feedView.Paint(e);
      rssView.Paint(e);
      rssDescriptionView.Paint(e);
    }

    private void backgroundChangeTimerTick(object sender, EventArgs e)
    {
      // Change the background image to the next image.
      currentImageIndex = (currentImageIndex + 1) % backgroundImages.Count;
    }

    void FadeTimer_Tick(object sender, EventArgs e)
    {
      this.Refresh();
    }

    void rssItemView_FadingComplete(object sender, EventArgs e)
    {
      if (rssView.SelectedIndex == (rssView.NumItems - 1))
      {
        rssView.NextArticle();
        feedView.NextArticle();
        itemList.Clear();
        foreach (Chan tempChan in feedView.SelectedFeed.Chans)
          foreach (Item tempItem in tempChan.Items)
            itemList.Add(tempItem);
        //rssView.Dispose();
        //rssView = new ItemListView("NRSS messages list", itemList);
        //InitializeRssView();
      }
      else
        rssView.NextArticle();
      rssDescriptionView.DisplayItem = rssView.SelectedItem;
    }
  }
}
