using System;
using System.Collections.Generic;
using System.Text;
using RSSReader.Properties;

namespace RSSReader
{
    public class Configuration
    {
        static private Configuration _instance = null;
       
        private Settings settings = new Settings();
        private string _login = "";
        private string _pass = "";
        private bool _isConnected = false;
        private bool _systray = false;
        private bool _tooltip = false;
        private int _updateTime = 5;
        private int _synthVolume = 50;
        private int _synthVoice = 2;
        private bool _useProxy = false;
        private string _proxyUrl = "";
        private int _proxyPort = 0;
        private string _proxyLogin = "";
        private string _proxyPass = "";
        private bool _rememberMe = true;

      

        #region Accessor
        static public Configuration Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new Configuration();
                return _instance;
            }
        }
        public string Login
        {
            get { return _login; }
            set { _login = value; }
        }
        public string Pass
        {
            get { return _pass; }
            set { _pass = value; }
        }
        public bool IsConnected
        {
            get { return _isConnected; }
            set { _isConnected = value; }
        }
        public bool Systray
        {
            get { return _systray; }
            set { _systray = value; }
        }
        public bool Tooltip
        {
            get { return _tooltip; }
            set { _tooltip = value; }
        }
        public int UpdateTime
        {
            get { return _updateTime; }
            set { _updateTime = value; }
        }
        public int SynthVolume
        {
            get { return _synthVolume; }
            set { _synthVolume = value; }
        }
        public int SynthVoice
        {
            get { return _synthVoice; }
            set { _synthVoice = value; }
        }
        public bool UseProxy
        {
            get { return _useProxy; }
            set { _useProxy = value; }
        }
        public string ProxyUrl
        {
            get { return _proxyUrl; }
            set { _proxyUrl = value; }
        }
        public int ProxyPort
        {
            get { return _proxyPort; }
            set { _proxyPort = value; }
        }
        public string ProxyLogin
        {
            get { return _proxyLogin; }
            set { _proxyLogin = value; }
        }
        public string ProxyPass
        {
            get { return _proxyPass; }
            set { _proxyPass = value; }
        }
        public bool RememberMe
        {
            get { return _rememberMe; }
            set { _rememberMe = value; }
        }
        #endregion

        public void Save()
        {
            if (_rememberMe == true)
            {
                settings.login = _login;
                settings.pass = _pass;
            }
          settings.systray = _systray;
          settings.tooltip = _tooltip;
          settings.updateTime = _updateTime;
          settings.synthVolume =_synthVolume;
          settings.synthVoice =_synthVoice;
          settings.useProxy =_useProxy;
          settings.proxyLogin =_proxyLogin;
          settings.proxyPass =_proxyPass;
          settings.proxyUrl =_proxyUrl;
          settings.proxyPort = _proxyPort;
          settings.rememberMe = _rememberMe;
            settings.Save();
        }

        public Configuration()
        {
            _login = settings.login;
            _pass = settings.pass;
            _systray = settings.systray;
            _tooltip = settings.tooltip;
            _updateTime = settings.updateTime;
            _synthVolume = settings.synthVolume;
            _synthVoice = settings.synthVoice;
            _useProxy = settings.useProxy;
            _proxyLogin = settings.proxyLogin;
            _proxyPass = settings.proxyPass;
            _proxyUrl = settings.proxyUrl;
            _proxyPort = settings.proxyPort;
            _rememberMe = settings.rememberMe;
        }
    }
}
