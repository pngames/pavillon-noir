using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using RSSScreenSaver.UI;
//using RSSScreenSaver.Rss;
using System.Net;
using Rss;

using System.Text;

using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

using System.Xml;

namespace RSSScreenSaver
{
    partial class ScreenSaverForm : Form
    {
        private RssFeed _rssFeed = new RssFeed();

        // The RssFeed to display articles from
       // private RssFeed rssFeed;

        // Objects for displaying RSS contents
        private ItemListView/*<RssItem>*/ rssView;
        private ItemDescriptionView/*<RssItem>*/ rssDescriptionView;
        private ChannelListView channelView;

        // The images to display in the background
        private List<Image> backgroundImages;
        private int currentImageIndex;

        // Keep track of whether the screensaver has become active.
        private bool isActive = false;

        // Keep track of the location of the mouse
        private Point mouseLocation;

        private List<string> imageExtensions = new List<string>(new string[] { "*.bmp", "*.gif", "*.png", "*.jpg", "*.jpeg" });

        public ScreenSaverForm()
        {
            InitializeComponent();

            SetupScreenSaver();
            LoadBackgroundImage();
            LoadRssFeed();

            rssView = new ItemListView(/*_rssFeed.Channels[0].Title, _rssFeed.Channels[0].Items*/);
            InitializeRssView();

            channelView = new ChannelListView(_rssFeed.Channels, ref rssView);
            InitializeChannelView();
           
            rssDescriptionView = new ItemDescriptionView();
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
           // WindowState = FormWindowState.Minimized;
            ShowInTaskbar = false;
           // ShowInTaskbar = true;
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
            backgroundImages.Add(Properties.Resources.Untitled_3);
        }


        private bool connectToServer(string log, string pass)
        {
            bool err = true;
            if (log != "t")
                err = false;
            if (pass != "t")
                err = false;
            return err;
        }

        private void LoadRssFeed()
        {
            HttpWebRequest request = null;
            bool err = true;
            
            //_rssFeed = RssFeed.ReadFromString(Properties.Resources.DefaultRSSText);
            if (connectToServer(Properties.Settings.Default.Login, Properties.Settings.Default.Login) == false)
                _rssFeed = RssFeed.ReadFromString(Properties.Resources.DefaultRSSTextUserError);
            else
            {
                int loop = 0;

                while (err == true )
                {
                    try
                    {
                        request = (HttpWebRequest)WebRequest.Create(new Uri("http://bluegloup.free.fr//news.xml"));
                        if (Properties.Settings.Default.UseProxy == true)
                        {
                            WebProxy proxy = new WebProxy(Properties.Settings.Default.ProxyUrl, Properties.Settings.Default.ProxyPort);
                            proxy.Credentials = new NetworkCredential(Properties.Settings.Default.ProxyLogin, Properties.Settings.Default.ProxyPass);
                            request.Proxy = proxy;
                        }
                        _rssFeed = RssFeed.Read(request);
                        err = false;
                    }
                    catch
                    {
                        err = true;
                        //_rssFeed = RssFeed.Read(Properties.Resources.DefaultRSSText);
                    }
                    if (loop > 10)
                        break;
                    loop++;
                }
                if (err == true)
                    _rssFeed = RssFeed.ReadFromString(Properties.Resources.DefaultRSSTextConnError);
            }
        

        }

        /// <summary>
        /// Initialize display properties of the rssView.
        /// </summary>
        private void InitializeRssView()
        {
            rssView.BackColor = Color.FromArgb(120, 240, 234, 232);
//            rssView.BorderColor = Color.White;
            rssView.BorderColor = Color.FromArgb(255, 227, 227, 227);         
            rssView.ForeColor = Color.FromArgb(255, 40, 40, 40);
           // rssView.SelectedBackColor = Color.FromArgb(200, 105, 61, 76);
            rssView.SelectedBackColor = Color.FromArgb(200, 152, 164, 111);
            //rssView.SelectedForeColor = Color.FromArgb(255, 204, 184, 163);
            rssView.SelectedForeColor = Color.FromArgb(255, 225, 241, 169);
            rssView.TitleBackColor = Color.Empty;
            //rssView.TitleForeColor = Color.FromArgb(255, 240, 234, 232);
            rssView.TitleForeColor = Color.FromArgb(200, 152, 164, 111);
           // rssView.TitleForeColor = Color.FromArgb(255, 204, 184, 163);
            rssView.MaxItemsToShow = 20;
            rssView.MinItemsToShow = 15;
            rssView.Location = new Point(Width / 10, Height / 10);
            rssView.Size = new Size(Width / 2, Height / 2);
         //   rssView.init();
        }

        private void InitializeChannelView()
        {
            channelView.BackColor = Color.FromArgb(120, 240, 234, 232);
           // channelView.BorderColor = Color.White;
            channelView.BorderColor = Color.FromArgb(255, 227, 227, 227);   
            channelView.ForeColor = Color.FromArgb(255, 40, 40, 40);
            //channelView.SelectedBackColor = Color.FromArgb(200, 105, 61, 76);
            //channelView.SelectedForeColor = Color.FromArgb(255, 204, 184, 163);
            channelView.SelectedBackColor = Color.FromArgb(200, 143, 159, 163);
            channelView.SelectedForeColor = Color.FromArgb(255, 221, 246, 253);
            channelView.TitleBackColor = Color.Empty;
            //rssView.TitleForeColor = Color.FromArgb(255, 240, 234, 232);
            channelView.TitleForeColor = Color.FromArgb(200, 143, 159, 163);
           // channelView.TitleForeColor = Color.FromArgb(255, 204, 184, 163);
            channelView.MaxItemsToShow = 10;
            channelView.MinItemsToShow = 10;
            
            // TODO
            channelView.Location = new Point(Width / 10, (Height / 8)+(Height / 2));
            channelView.Size = new Size(Width / 2, Height / 3);
           
        }

        /// <summary>
        /// Initialize display properties of the rssDescriptionView.
        /// </summary>
        private void InitializeRssDescriptionView()
        {
           rssDescriptionView.DisplayItem = rssView.SelectedItem;
            //rssDescriptionView.ForeColor = Color.FromArgb(255, 240, 234, 232);
           rssDescriptionView.ForeColor = Color.FromArgb(200, 105, 61, 76);
            rssDescriptionView.TitleFont = rssView.TitleFont;
            rssDescriptionView.LineColor = Color.FromArgb(120, 240, 234, 232);
            rssDescriptionView.LineWidth = 2f;
            rssDescriptionView.FadeTimer.Tick += new EventHandler(FadeTimer_Tick);
            rssDescriptionView.FadeTimer.Interval = Properties.Settings.Default.FadeTime;

            //rssDescriptionView.Location = new Point(3 * Width / 4, Height / 3);
            //rssDescriptionView.Size = new Size(Width / 4, Height / 2);

            rssDescriptionView.Location = new Point(3 * Width / 4, Height / 3);
            rssDescriptionView.Size = new Size(Width / 4, Height / 2);
            
            rssDescriptionView.FadingComplete += new EventHandler(rssItemView_FadingComplete);
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
                 //   Close();
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
            rssView.Paint(e);
            channelView.Paint(e);
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
            if (rssView.SelectedIndex == rssView.NbItems-1 )
                channelView.NextArticle();

            rssView.NextArticle();
            
            rssDescriptionView.DisplayItem = rssView.SelectedItem;
        }
    }
}
