﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.26
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// 
// This source code was auto-generated by Microsoft.VSDesigner, Version 2.0.50727.26.
// 
#pragma warning disable 1591

namespace NRSS.Winformclient.NRSSServer {
    using System.Diagnostics;
    using System.Web.Services;
    using System.ComponentModel;
    using System.Web.Services.Protocols;
    using System;
    using System.Xml.Serialization;
    
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Web.Services.WebServiceBindingAttribute(Name="ServiceSoap", Namespace="http://nrss.org/")]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(Chan))]
    public partial class Service : System.Web.Services.Protocols.SoapHttpClientProtocol {
        
        private System.Threading.SendOrPostCallback testRSSOperationCompleted;
        
        private System.Threading.SendOrPostCallback getSupportedTypesOperationCompleted;
        
        private System.Threading.SendOrPostCallback createUserOperationCompleted;
        
        private System.Threading.SendOrPostCallback validateUserOperationCompleted;
        
        private System.Threading.SendOrPostCallback logonOperationCompleted;
        
        private System.Threading.SendOrPostCallback getFeedsOperationCompleted;
        
        private System.Threading.SendOrPostCallback setAsReadOperationCompleted;
        
        private bool useDefaultCredentialsSetExplicitly;
        
        /// <remarks/>
        public Service() {
            this.Url = global::NRSS.Winformclient.Properties.Settings.Default.NRSS_Winformclient_NRSSServer_Service;
            if ((this.IsLocalFileSystemWebService(this.Url) == true)) {
                this.UseDefaultCredentials = true;
                this.useDefaultCredentialsSetExplicitly = false;
            }
            else {
                this.useDefaultCredentialsSetExplicitly = true;
            }
        }
        
        public new string Url {
            get {
                return base.Url;
            }
            set {
                if ((((this.IsLocalFileSystemWebService(base.Url) == true) 
                            && (this.useDefaultCredentialsSetExplicitly == false)) 
                            && (this.IsLocalFileSystemWebService(value) == false))) {
                    base.UseDefaultCredentials = false;
                }
                base.Url = value;
            }
        }
        
        public new bool UseDefaultCredentials {
            get {
                return base.UseDefaultCredentials;
            }
            set {
                base.UseDefaultCredentials = value;
                this.useDefaultCredentialsSetExplicitly = true;
            }
        }
        
        /// <remarks/>
        public event testRSSCompletedEventHandler testRSSCompleted;
        
        /// <remarks/>
        public event getSupportedTypesCompletedEventHandler getSupportedTypesCompleted;
        
        /// <remarks/>
        public event createUserCompletedEventHandler createUserCompleted;
        
        /// <remarks/>
        public event validateUserCompletedEventHandler validateUserCompleted;
        
        /// <remarks/>
        public event logonCompletedEventHandler logonCompleted;
        
        /// <remarks/>
        public event getFeedsCompletedEventHandler getFeedsCompleted;
        
        /// <remarks/>
        public event setAsReadCompletedEventHandler setAsReadCompleted;
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/testRSS", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public Feed testRSS() {
            object[] results = this.Invoke("testRSS", new object[0]);
            return ((Feed)(results[0]));
        }
        
        /// <remarks/>
        public void testRSSAsync() {
            this.testRSSAsync(null);
        }
        
        /// <remarks/>
        public void testRSSAsync(object userState) {
            if ((this.testRSSOperationCompleted == null)) {
                this.testRSSOperationCompleted = new System.Threading.SendOrPostCallback(this.OntestRSSOperationCompleted);
            }
            this.InvokeAsync("testRSS", new object[0], this.testRSSOperationCompleted, userState);
        }
        
        private void OntestRSSOperationCompleted(object arg) {
            if ((this.testRSSCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.testRSSCompleted(this, new testRSSCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/getSupportedTypes", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public ImportType[] getSupportedTypes() {
            object[] results = this.Invoke("getSupportedTypes", new object[0]);
            return ((ImportType[])(results[0]));
        }
        
        /// <remarks/>
        public void getSupportedTypesAsync() {
            this.getSupportedTypesAsync(null);
        }
        
        /// <remarks/>
        public void getSupportedTypesAsync(object userState) {
            if ((this.getSupportedTypesOperationCompleted == null)) {
                this.getSupportedTypesOperationCompleted = new System.Threading.SendOrPostCallback(this.OngetSupportedTypesOperationCompleted);
            }
            this.InvokeAsync("getSupportedTypes", new object[0], this.getSupportedTypesOperationCompleted, userState);
        }
        
        private void OngetSupportedTypesOperationCompleted(object arg) {
            if ((this.getSupportedTypesCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.getSupportedTypesCompleted(this, new getSupportedTypesCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/createUser", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public void createUser(User user) {
            this.Invoke("createUser", new object[] {
                        user});
        }
        
        /// <remarks/>
        public void createUserAsync(User user) {
            this.createUserAsync(user, null);
        }
        
        /// <remarks/>
        public void createUserAsync(User user, object userState) {
            if ((this.createUserOperationCompleted == null)) {
                this.createUserOperationCompleted = new System.Threading.SendOrPostCallback(this.OncreateUserOperationCompleted);
            }
            this.InvokeAsync("createUser", new object[] {
                        user}, this.createUserOperationCompleted, userState);
        }
        
        private void OncreateUserOperationCompleted(object arg) {
            if ((this.createUserCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.createUserCompleted(this, new System.ComponentModel.AsyncCompletedEventArgs(invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/validateUser", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public void validateUser(string hash) {
            this.Invoke("validateUser", new object[] {
                        hash});
        }
        
        /// <remarks/>
        public void validateUserAsync(string hash) {
            this.validateUserAsync(hash, null);
        }
        
        /// <remarks/>
        public void validateUserAsync(string hash, object userState) {
            if ((this.validateUserOperationCompleted == null)) {
                this.validateUserOperationCompleted = new System.Threading.SendOrPostCallback(this.OnvalidateUserOperationCompleted);
            }
            this.InvokeAsync("validateUser", new object[] {
                        hash}, this.validateUserOperationCompleted, userState);
        }
        
        private void OnvalidateUserOperationCompleted(object arg) {
            if ((this.validateUserCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.validateUserCompleted(this, new System.ComponentModel.AsyncCompletedEventArgs(invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/logon", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public User logon(string user, string pass) {
            object[] results = this.Invoke("logon", new object[] {
                        user,
                        pass});
            return ((User)(results[0]));
        }
        
        /// <remarks/>
        public void logonAsync(string user, string pass) {
            this.logonAsync(user, pass, null);
        }
        
        /// <remarks/>
        public void logonAsync(string user, string pass, object userState) {
            if ((this.logonOperationCompleted == null)) {
                this.logonOperationCompleted = new System.Threading.SendOrPostCallback(this.OnlogonOperationCompleted);
            }
            this.InvokeAsync("logon", new object[] {
                        user,
                        pass}, this.logonOperationCompleted, userState);
        }
        
        private void OnlogonOperationCompleted(object arg) {
            if ((this.logonCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.logonCompleted(this, new logonCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/getFeeds", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public Feed[] getFeeds(string uid) {
            object[] results = this.Invoke("getFeeds", new object[] {
                        uid});
            return ((Feed[])(results[0]));
        }
        
        /// <remarks/>
        public void getFeedsAsync(string uid) {
            this.getFeedsAsync(uid, null);
        }
        
        /// <remarks/>
        public void getFeedsAsync(string uid, object userState) {
            if ((this.getFeedsOperationCompleted == null)) {
                this.getFeedsOperationCompleted = new System.Threading.SendOrPostCallback(this.OngetFeedsOperationCompleted);
            }
            this.InvokeAsync("getFeeds", new object[] {
                        uid}, this.getFeedsOperationCompleted, userState);
        }
        
        private void OngetFeedsOperationCompleted(object arg) {
            if ((this.getFeedsCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.getFeedsCompleted(this, new getFeedsCompletedEventArgs(invokeArgs.Results, invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://nrss.org/setAsRead", RequestNamespace="http://nrss.org/", ResponseNamespace="http://nrss.org/", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public void setAsRead(string uid, Item item) {
            this.Invoke("setAsRead", new object[] {
                        uid,
                        item});
        }
        
        /// <remarks/>
        public void setAsReadAsync(string uid, Item item) {
            this.setAsReadAsync(uid, item, null);
        }
        
        /// <remarks/>
        public void setAsReadAsync(string uid, Item item, object userState) {
            if ((this.setAsReadOperationCompleted == null)) {
                this.setAsReadOperationCompleted = new System.Threading.SendOrPostCallback(this.OnsetAsReadOperationCompleted);
            }
            this.InvokeAsync("setAsRead", new object[] {
                        uid,
                        item}, this.setAsReadOperationCompleted, userState);
        }
        
        private void OnsetAsReadOperationCompleted(object arg) {
            if ((this.setAsReadCompleted != null)) {
                System.Web.Services.Protocols.InvokeCompletedEventArgs invokeArgs = ((System.Web.Services.Protocols.InvokeCompletedEventArgs)(arg));
                this.setAsReadCompleted(this, new System.ComponentModel.AsyncCompletedEventArgs(invokeArgs.Error, invokeArgs.Cancelled, invokeArgs.UserState));
            }
        }
        
        /// <remarks/>
        public new void CancelAsync(object userState) {
            base.CancelAsync(userState);
        }
        
        private bool IsLocalFileSystemWebService(string url) {
            if (((url == null) 
                        || (url == string.Empty))) {
                return false;
            }
            System.Uri wsUri = new System.Uri(url);
            if (((wsUri.Port >= 1024) 
                        && (string.Compare(wsUri.Host, "localHost", System.StringComparison.OrdinalIgnoreCase) == 0))) {
                return true;
            }
            return false;
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.26")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://nrss.org/")]
    public partial class Feed {
        
        private int idField;
        
        private string typeField;
        
        private string nameField;
        
        private string filsField;
        
        private int filsPortField;
        
        private string filsUserField;
        
        private string filsPassField;
        
        private object[] chansField;
        
        /// <remarks/>
        public int Id {
            get {
                return this.idField;
            }
            set {
                this.idField = value;
            }
        }
        
        /// <remarks/>
        public string Type {
            get {
                return this.typeField;
            }
            set {
                this.typeField = value;
            }
        }
        
        /// <remarks/>
        public string Name {
            get {
                return this.nameField;
            }
            set {
                this.nameField = value;
            }
        }
        
        /// <remarks/>
        public string Fils {
            get {
                return this.filsField;
            }
            set {
                this.filsField = value;
            }
        }
        
        /// <remarks/>
        public int FilsPort {
            get {
                return this.filsPortField;
            }
            set {
                this.filsPortField = value;
            }
        }
        
        /// <remarks/>
        public string FilsUser {
            get {
                return this.filsUserField;
            }
            set {
                this.filsUserField = value;
            }
        }
        
        /// <remarks/>
        public string FilsPass {
            get {
                return this.filsPassField;
            }
            set {
                this.filsPassField = value;
            }
        }
        
        /// <remarks/>
        public object[] Chans {
            get {
                return this.chansField;
            }
            set {
                this.chansField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.26")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://nrss.org/")]
    public partial class User {
        
        private string idField;
        
        private string emailField;
        
        private string passwdField;
        
        private bool confirmedField;
        
        private string creationField;
        
        private string lastLogonField;
        
        private object[] groupsField;
        
        private object[] readItemsField;
        
        /// <remarks/>
        public string Id {
            get {
                return this.idField;
            }
            set {
                this.idField = value;
            }
        }
        
        /// <remarks/>
        public string Email {
            get {
                return this.emailField;
            }
            set {
                this.emailField = value;
            }
        }
        
        /// <remarks/>
        public string Passwd {
            get {
                return this.passwdField;
            }
            set {
                this.passwdField = value;
            }
        }
        
        /// <remarks/>
        public bool Confirmed {
            get {
                return this.confirmedField;
            }
            set {
                this.confirmedField = value;
            }
        }
        
        /// <remarks/>
        public string Creation {
            get {
                return this.creationField;
            }
            set {
                this.creationField = value;
            }
        }
        
        /// <remarks/>
        public string LastLogon {
            get {
                return this.lastLogonField;
            }
            set {
                this.lastLogonField = value;
            }
        }
        
        /// <remarks/>
        public object[] Groups {
            get {
                return this.groupsField;
            }
            set {
                this.groupsField = value;
            }
        }
        
        /// <remarks/>
        public object[] ReadItems {
            get {
                return this.readItemsField;
            }
            set {
                this.readItemsField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.26")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://nrss.org/")]
    public partial class ImportType {
        
        private string nameField;
        
        private string descriptionField;
        
        private int defaultPortField;
        
        /// <remarks/>
        public string Name {
            get {
                return this.nameField;
            }
            set {
                this.nameField = value;
            }
        }
        
        /// <remarks/>
        public string Description {
            get {
                return this.descriptionField;
            }
            set {
                this.descriptionField = value;
            }
        }
        
        /// <remarks/>
        public int DefaultPort {
            get {
                return this.defaultPortField;
            }
            set {
                this.defaultPortField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.26")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://nrss.org/")]
    public partial class Chan {
        
        private int idField;
        
        private string titleField;
        
        private string descriptionField;
        
        private string languageField;
        
        private string linkField;
        
        private object[] itemsField;
        
        /// <remarks/>
        public int Id {
            get {
                return this.idField;
            }
            set {
                this.idField = value;
            }
        }
        
        /// <remarks/>
        public string Title {
            get {
                return this.titleField;
            }
            set {
                this.titleField = value;
            }
        }
        
        /// <remarks/>
        public string Description {
            get {
                return this.descriptionField;
            }
            set {
                this.descriptionField = value;
            }
        }
        
        /// <remarks/>
        public string Language {
            get {
                return this.languageField;
            }
            set {
                this.languageField = value;
            }
        }
        
        /// <remarks/>
        public string Link {
            get {
                return this.linkField;
            }
            set {
                this.linkField = value;
            }
        }
        
        /// <remarks/>
        public object[] Items {
            get {
                return this.itemsField;
            }
            set {
                this.itemsField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.26")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace="http://nrss.org/")]
    public partial class Item {
        
        private int idField;
        
        private string messageIDField;
        
        private string authorField;
        
        private System.DateTime dateField;
        
        private string titleField;
        
        private string descriptionField;
        
        private string contentField;
        
        private string linkField;
        
        private Item parentField;
        
        private bool readField;
        
        /// <remarks/>
        public int Id {
            get {
                return this.idField;
            }
            set {
                this.idField = value;
            }
        }
        
        /// <remarks/>
        public string MessageID {
            get {
                return this.messageIDField;
            }
            set {
                this.messageIDField = value;
            }
        }
        
        /// <remarks/>
        public string Author {
            get {
                return this.authorField;
            }
            set {
                this.authorField = value;
            }
        }
        
        /// <remarks/>
        public System.DateTime Date {
            get {
                return this.dateField;
            }
            set {
                this.dateField = value;
            }
        }
        
        /// <remarks/>
        public string Title {
            get {
                return this.titleField;
            }
            set {
                this.titleField = value;
            }
        }
        
        /// <remarks/>
        public string Description {
            get {
                return this.descriptionField;
            }
            set {
                this.descriptionField = value;
            }
        }
        
        /// <remarks/>
        public string Content {
            get {
                return this.contentField;
            }
            set {
                this.contentField = value;
            }
        }
        
        /// <remarks/>
        public string Link {
            get {
                return this.linkField;
            }
            set {
                this.linkField = value;
            }
        }
        
        /// <remarks/>
        public Item Parent {
            get {
                return this.parentField;
            }
            set {
                this.parentField = value;
            }
        }
        
        /// <remarks/>
        public bool Read {
            get {
                return this.readField;
            }
            set {
                this.readField = value;
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void testRSSCompletedEventHandler(object sender, testRSSCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class testRSSCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal testRSSCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public Feed Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((Feed)(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void getSupportedTypesCompletedEventHandler(object sender, getSupportedTypesCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class getSupportedTypesCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal getSupportedTypesCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public ImportType[] Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((ImportType[])(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void createUserCompletedEventHandler(object sender, System.ComponentModel.AsyncCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void validateUserCompletedEventHandler(object sender, System.ComponentModel.AsyncCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void logonCompletedEventHandler(object sender, logonCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class logonCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal logonCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public User Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((User)(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void getFeedsCompletedEventHandler(object sender, getFeedsCompletedEventArgs e);
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    public partial class getFeedsCompletedEventArgs : System.ComponentModel.AsyncCompletedEventArgs {
        
        private object[] results;
        
        internal getFeedsCompletedEventArgs(object[] results, System.Exception exception, bool cancelled, object userState) : 
                base(exception, cancelled, userState) {
            this.results = results;
        }
        
        /// <remarks/>
        public Feed[] Result {
            get {
                this.RaiseExceptionIfNecessary();
                return ((Feed[])(this.results[0]));
            }
        }
    }
    
    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Web.Services", "2.0.50727.26")]
    public delegate void setAsReadCompletedEventHandler(object sender, System.ComponentModel.AsyncCompletedEventArgs e);
}

#pragma warning restore 1591