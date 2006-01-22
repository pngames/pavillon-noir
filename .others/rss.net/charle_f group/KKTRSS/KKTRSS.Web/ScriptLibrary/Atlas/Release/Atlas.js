//-----------------------------------------------------------------------
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------
// Atlas.js
// Atlas Framework.
Function.abstractMethod =function(){throw 'Abstract method should be implemented';}
Function.createCallback =function(method,context){return function(){method(context);}
}
Function.createCallbackWithArguments =function(method,context){return function(){var args =[];for (var i =2;i <arguments.length;i++){args.add(arguments[i]);}
args.add(context);method.apply(null,args);}
}
Function.createDelegate =function(instance,method){return function(){method.apply(instance,arguments);}
}
Function.emptyMethod =function(){}
Function.prototype.getBaseMethod =function(instance,methodName){var baseMethod =null;var baseType =this.getBaseType();if (baseType){var directBaseType =baseType;if (instance._baseMethods){while (baseType){var methodKey =baseType.getName()+'.'+methodName;var method =instance._baseMethods[methodKey];if (method){return method;}
baseType =baseType._baseType;}
}
if (!baseMethod){return directBaseType.prototype[methodName];}
}
return null;}
Function.prototype.getBaseType =function(){return this._baseType;}
Function.prototype.getName =function(){return this._typeName;}
Function.parse =function(functionName){var fn =null;try {eval('fn = '+functionName);if (typeof(fn)!='function'){fn =null;}
}
catch (ex){}
return fn;}
Function.prototype._processBaseType =function(){if (this._basePrototypePending){var baseType =this._baseType;baseType._processBaseType();for (var memberName in baseType.prototype){var memberValue =baseType.prototype[memberName];if (!this.prototype[memberName]){this.prototype[memberName]=memberValue;}
}
delete this._basePrototypePending;}
}
Function.prototype.callBaseMethod =function(instance,methodName,baseArguments){var baseMethod =this.getBaseMethod(instance,methodName);if (baseMethod){if (!baseArguments){return baseMethod.apply(instance);}
else {return baseMethod.apply(instance,baseArguments);}
}
return null;}
Function.prototype.implementsInterface =function(interfaceType){var interfaces =this._interfaces;if (interfaces){if (interfaces.contains(interfaceType)){return true;}
}
var baseType =this._baseType;while (baseType){interfaces =baseType._interfaces;if (interfaces){if (interfaces.contains(interfaceType)){return true;}
}
baseType =baseType._baseType;}
return false;}
Function.prototype.inheritsFrom =function(parentType){var baseType =this._baseType;while (baseType){if (baseType ==parentType){return true;}
baseType =baseType._baseType;}
return false;}
Function.prototype.initializeBase =function(instance,baseArguments){this._processBaseType();if (this._interfaces){for (var i =0;i <this._interfaces.length;i++){this._interfaces[i].call(instance);}
}
if (this._baseType){if (!baseArguments){this._baseType.apply(instance);}
else {this._baseType.apply(instance,baseArguments);}
}
return instance;}
Function.prototype.isImplementedBy =function(instance){if (!instance)return false;var instanceType =Object.getType(instance);return instanceType.implementsInterface(this);}
Function.prototype.isInstanceOfType =function(instance){if (typeof(instance)=='undefined'||instance ==null){return false;}
if (instance instanceof this){return true;}
var instanceType =Object.getType(instance);if (instanceType ==this){return true;}
return instanceType.inheritsFrom(this);}
Function.prototype.registerBaseMethod =function(instance,methodName){if (!instance._baseMethods){instance._baseMethods ={};}
var methodKey =this.getName()+'.'+methodName;instance._baseMethods[methodKey]=instance[methodName];}
Function.createInstance =function(type){if (typeof(type)!='function'){type =Function.parse(type);}
return new type();}
Function.registerClass =function(typeName,baseType,interfaceType){var type =Function.parse(typeName);if (window.__safari){eval(typeName +'.prototype.constructor = '+typeName +';');}
type._typeName =typeName;if (baseType){type._baseType =baseType;type._basePrototypePending =true;}
if (interfaceType){type._interfaces =[];for (var i =2;i <arguments.length;i++){interfaceType =arguments[i];type._interfaces.add(interfaceType);}
}
return type;}
Function.registerAbstractClass =function(typeName,baseType){var type =Type.registerClass.apply(null,arguments);type._abstract =true;return type;}
Function.registerSealedClass =function(typeName,baseType){var type =Type.registerClass.apply(null,arguments);type._sealed =true;return type;}
Function.registerInterface =function(typeName){var type =Function.parse(typeName);type._typeName =typeName;type._interface =true;type._abstract =true;type._sealed =true;return type;}
Function.registerNamespace =function(namespacePath){var rootObject =window;var namespaceParts =namespacePath.split('.');for (var i =0;i <namespaceParts.length;i++){var currentPart =namespaceParts[i];if (!rootObject[currentPart]){rootObject[currentPart]=new Object();}
rootObject =rootObject[currentPart];}
}
Function._typeName ='Function';window.Type =Function;Object.getType =function(instance){return instance.constructor;}
Object._typeName ='Object';Boolean.parse =function(value){if (typeof(value)=='string'){return (value.toLowerCase()=='true');}
return value ?true :false;}
Number.parse =function(value){if (!value ||(value.length ==0)){return 0;}
return parseFloat(value);}
Number._typeName ='Number';String.prototype.endsWith =function(suffix){return (this.substr(this.length -suffix.length)==suffix);}
String.prototype.startsWith =function(prefix){return (this.substr(0,prefix.length)==prefix);}
String.prototype.trimLeft =function(){return this.replace(/^\s*/,"");}
String.prototype.trimRight =function(){return this.replace(/\s*$/,"");}
String.prototype.trim =function(){return this.trimRight().trimLeft();}
String.format =function(format){for (var i =1;i <arguments.length;i++){format =format.replace("{"+(i -1)+"}",arguments[i]);}
return format;}
String._typeName ='String';Array.prototype.add =function(item){this.push(item);}
Array.prototype.addRange =function(items){var length =items.length;if (length !=0){for (var index =0;index <length;index++){this.push(items[index]);}
}
}
Array.prototype.clear =function(){if (this.length >0){this.splice(0,this.length);}
}
Array.prototype.clone =function(){var clonedArray =[];var length =this.length;for (var index =0;index <length;index++){clonedArray[index]=this[index];}
return clonedArray;}
Array.prototype.contains =function(item){var index =this.indexOf(item);return (index >=0);}
Array.prototype.dequeue =function(){return this.shift();}
Array.prototype.indexOf =function(item){var length =this.length;if (length !=0){for (var index =0;index <length;index++){if (this[index]==item){return index;}
}
}
return -1;}
Array.prototype.insert =function(index,item){this.splice(index,0,item);}
Array.prototype.queue =function(item){this.push(item);}
Array.prototype.remove =function(item){var index =this.indexOf(item);if (index >=0){this.splice(index,1);}
}
Array.prototype.removeAt =function(index){this.splice(index,1);}
Array._typeName ='Array';Array.parse =function(value){return eval('('+value +')');}
RegExp.parse =function(value){if (value.startsWith('/')){var endSlashIndex =value.lastIndexOf('/');if (endSlashIndex >1){var expression =value.substring(1,endSlashIndex);var flags =value.substr(endSlashIndex +1);return new RegExp(expression,flags);}
}
return null;}
RegExp._typeName ='RegExp';Date._typeName ='Date';Date.prototype.serialize =function(){var stringBuilder =new Web.StringBuilder();stringBuilder.append('new Date(');stringBuilder.append(Date.UTC(this.getUTCFullYear(),this.getUTCMonth(),this.getUTCDate(),this.getUTCHours(),this.getUTCMinutes(),this.getUTCSeconds(),this.getUTCMilliseconds()));stringBuilder.append(')');return stringBuilder.toString();}
Type.registerNamespace('Web');Web._Debug =function(){this.assert =function(condition,message,displayCaller){if (!condition){message ='Assertion Failed: '+message +(displayCaller ?'\r\nat '+this.assert.caller :'');if (confirm(message +'\r\n\r\nBreak into debugger?')){this.fail(message);}
}
}
this.clearTrace =function(){var traceElement =document.getElementById('__atlas_trace');if (traceElement){var children =traceElement.childNodes;for(var i =children.length -2;i >0;i--){traceElement.removeChild(children[i]);}
document.getElementById('__atlas_trace').style.display ='none';}
}
this.dump =function(object,name,recursive,indentationPadding,loopArray){name =name ?name :'';indentationPadding =indentationPadding ?indentationPadding :'';if (object ==null){this.trace(indentationPadding +name +': null');return;}
switch(typeof(object)){case 'undefined':this.trace(indentationPadding +name +': Undefined');break;case 'number':case 'string':case 'boolean':this.trace(indentationPadding +name +': '+object);break;default:if (!loopArray){loopArray =[];}
else if (loopArray.contains(object)){this.trace(indentationPadding +name +': ...');return;}
loopArray.add(object);var type =Object.getType(object);if (type !=null){var typeName =type.getName();this.trace(indentationPadding +name +(typeof(typeName)=='string'?' {'+typeName +'}':''));if ((indentationPadding =='')||recursive){indentationPadding +='+';var i,length,properties,p,v;if (Web.IArray.isImplementedBy(object)){length =object.get_length();for (i =0;i <length;i++){this.dump(object.getItem(i),'['+i +']',recursive,indentationPadding,loopArray);}
}
if (Web.ITypeDescriptorProvider.isImplementedBy(object)){var td =Web.TypeDescriptor.getTypeDescriptor(object);properties =td._getProperties();for (p in properties){var propertyInfo =properties[p];if (propertyInfo.name){v =Web.TypeDescriptor.getProperty(object,propertyInfo.name);this.dump(v,p,recursive,indentationPadding,loopArray);}
}
}
else {for (p in object){v =object[p];if (!Function.isInstanceOfType(v)&&!Web.Event.isInstanceOfType(v)){this.dump(v,p,recursive,indentationPadding,loopArray);}
}
}
}
}
else {var tagName =object.tagName;var attributes =object.attributes;if (tagName &&attributes){this.trace(indentationPadding +name +' {'+tagName +'}');indentationPadding +='+';length =attributes.length;for (var i =0;i <length;i++){var val =attributes[i].nodeValue;if (val){this.dump(val,attributes[i].nodeName,recursive,indentationPadding,loopArray);}
}
}
else {this.trace('Unknown object');}
}
loopArray.remove(object);}
}
this.fail =function(message){Debug.breakIntoDebugger(message);}
this.trace =function(text){Debug.writeln(text);var traceElement =document.getElementById('__atlas_trace');if (!traceElement){traceElement =document.createElement('FIELDSET');traceElement.id ='__atlas_trace';traceElement.style.backgroundColor ='white';traceElement.style.color ='black';traceElement.style.textAlign ='left';traceElement.style.font ='normal normal normal 1em/1.1em verdana,sans-serif';var legend =document.createElement('LEGEND');var legendText =document.createTextNode('Debugging Trace');legend.appendChild(legendText);traceElement.appendChild(legend);var clearButton =document.createElement('INPUT');clearButton.type ='button';clearButton.value ='Clear Trace';clearButton.onclick =debug.clearTrace;traceElement.appendChild(clearButton);document.body.appendChild(traceElement);}
var traceLine =document.createElement('DIV');traceLine.innerHTML =text;traceElement.insertBefore(traceLine,traceElement.childNodes[traceElement.childNodes.length -1]);traceElement.style.display ='block';}
}
window.debug =new Web._Debug();Web.Enum =new function(){function getValues(){if (!this._values){var values ={};for (var f in this){if (typeof(this[f])!='function'){values[f]=this[f];}
}
this._values =values;}
return this._values;}
function valueFromString(s){for (var f in this){if (f ==s){return this[f];}
}
throw 'Invalid Enumeration Value';}
function valueToString(value){for (var i in this){if (this[i]==value){return i;}
}
throw 'Invalid Enumeration Value';}
this.create =function(){var enumeration ={};enumeration.getValues =getValues;enumeration.parse =valueFromString;enumeration.toString =valueToString;for (var i =0;i <arguments.length;i++){enumeration[arguments[i]]=i;}
return enumeration;}
}
Web.Flags =new function(){function valueFromString(s){var parts =s.split('|');var value =0;for (var i =parts.length -1;i >=0;i--){var part =parts[i].trim();var found =false;for (var f in this){if (f ==part){value |=this[f];found =true;break;}
}
if (found ==false){throw 'Invalid Enumeration Value';}
}
return value;}
function valueToString(value){var sb =new Web.StringBuilder();for (var i in this){if ((this[i]&value)!=0){if (sb.isEmpty()==false){sb.append(' | ');}
sb.append(i);}
}
return sb.toString();}
this.create =function(){var flags =new Object();flags.parse =valueFromString;flags.toString =valueToString;for (var i =0;i <arguments.length;i +=2){var name =arguments[i];var value =arguments[i +1];flags[name]=value;}
return flags;}
}
Web.Attributes =new function(){this.defineAttribute =function(attributeName){this[attributeName]=attributeName;}
}
Web.IArray =function(){this.get_length =Function.abstractMethod;this.getItem =Function.abstractMethod;}
Type.registerInterface("Web.IArray");Array.prototype.get_length =function(){return this.length;}
Array.prototype.getItem =function(index){return this[index];}
Array._interfaces =[];Array._interfaces.add(Web.IArray);Web.IDisposable =function(){this.dispose =Function.abstractMethod;}
Type.registerInterface('Web.IDisposable');Web.StringBuilder =function(initialText){var _parts =new Array();if ((typeof(initialText)=='string')&&(initialText.length !=0)){_parts.add(initialText);}
this.append =function(text){if ((text ==null)||(typeof(text)=='undefined')){return;}
if ((typeof(text)=='string')&&(text.length ==0)){return;}
_parts.add(text);}
this.appendLine =function(text){this.append(text);_parts.add('\r\n');}
this.clear =function(){_parts.clear();}
this.isEmpty =function(){return (_parts.length ==0);}
this.toString =function(delimiter){delimiter =delimiter ||'';return _parts.join(delimiter);}
}
Type.registerSealedClass('Web.StringBuilder');Web.Attributes.defineAttribute('Element');Web.TypeDescriptor =function(){var _properties ={};var _events ={};var _methods ={};var _attributes ={};this._getAttributes =function(){return _attributes;}
this._getEvents =function(){return _events;}
this._getMethods =function(){return _methods;}
this._getProperties =function(){return _properties;}
}
Web.TypeDescriptor.prototype.addAttribute =function(attributeName,attributeValue){this._getAttributes()[attributeName]=attributeValue;}
Web.TypeDescriptor.prototype.addEvent =function(eventName,supportsActions){this._getEvents()[eventName]={name:eventName,actions:supportsActions };}
Web.TypeDescriptor.prototype.addMethod =function(methodName,associatedParameters){this._getMethods()[methodName]={name:methodName,parameters:associatedParameters };}
Web.TypeDescriptor.prototype.addProperty =function(propertyName,propertyType,readOnly){if (!readOnly){readOnly =false;}
var associatedAttributes;if (arguments.length >3){associatedAttributes ={};for (var i =3;i <arguments.length;i +=2){var attribute =arguments[i];var value =arguments[i +1];associatedAttributes[attribute]=value;}
}
this._getProperties()[propertyName]={name:propertyName,type:propertyType,isReadOnly:readOnly,attributes:associatedAttributes };}
Web.TypeDescriptor.addType =function(tagPrefix,tagName,type){if (!Web.TypeDescriptor._registeredTags){Web.TypeDescriptor._registeredTags ={};}
var tagTable =Web.TypeDescriptor._registeredTags[tagPrefix];if (!tagTable){tagTable ={};Web.TypeDescriptor._registeredTags[tagPrefix]=tagTable;}
tagTable[tagName]=type;}
Web.TypeDescriptor.createParameter =function(parameterName,parameterType){return {name:parameterName,type:parameterType };}
Web.TypeDescriptor.getType =function(tagPrefix,tagName){if (Web.TypeDescriptor._registeredTags){var tagNameTable =Web.TypeDescriptor._registeredTags[tagPrefix];if (tagNameTable){return tagNameTable[tagName];}
}
return null;}
Web.TypeDescriptor.getTypeDescriptor =function(instance){var type =Object.getType(instance);var td =type._descriptor;if (!td){td =instance.getDescriptor();type._descriptor =td;}
return td;}
Web.TypeDescriptor.initializeInstance =function(instance,node,markupContext){var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (!td){return null;}
var supportsBatchedUpdates =false;if (Web.ISupportBatchedUpdates.isImplementedBy(instance)){supportsBatchedUpdates =true;instance.beginUpdate();}
var i,a;var attr,attrName;var propertyInfo,propertyName,propertyType,propertyValue;var eventInfo,eventValue;var setter,getter;var properties =td._getProperties();var events =td._getEvents();var attributes =node.attributes;if (attributes){for (a =attributes.length -1;a >=0;a--){attr =attributes[a];attrName =attr.nodeName;propertyInfo =properties[attrName];if (propertyInfo){propertyType =propertyInfo.type;propertyValue =attr.nodeValue;var delayedSet =false;if (propertyType ==Object){var elementsOnly =(propertyInfo.attributes &&propertyInfo.attributes[Web.Attributes.Element]);if (!elementsOnly){markupContext.addReference(instance,propertyInfo,propertyValue);delayedSet =true;}
else {propertyValue =markupContext.findObject(propertyValue,elementsOnly);}
}
if (!delayedSet){propertyName =propertyInfo.name;setter =instance['set_'+propertyName];if (propertyType !=Object){if (propertyType ==Array){propertyValue =Array.parse('['+propertyValue +']');}
else if (propertyType !=String){propertyValue =propertyType.parse(propertyValue);}
}
setter.call(instance,propertyValue);}
}
else {eventInfo =events[attrName];if (eventInfo){var handler =Function.parse(attr.nodeValue);if (handler){eventValue =instance[eventInfo.name];eventValue.add(handler);}
}
}
}
}
var childNodes =node.childNodes;if (childNodes &&(childNodes.length !=0)){for (i =childNodes.length -1;i >=0;i--){var childNode =childNodes[i];var nodeName =childNode.baseName;propertyInfo =properties[nodeName];if (propertyInfo){propertyName =propertyInfo.name;propertyType =propertyInfo.type;if (propertyInfo.isReadOnly){getter =instance['get_'+propertyName];var nestedObject =getter.call(instance);if (propertyType ==Array){if (childNode.childNodes.length !=0){var items =Web.TypeDescriptor.processMarkupNodes(childNode.childNodes,markupContext);for (var itemIndex =0;itemIndex <items.length;itemIndex++){nestedObject.add(items[itemIndex]);}
}
}
else if (propertyType ==Object){attributes =childNode.attributes;for (a =attributes.length -1;a >=0;a--){attr =attributes[a];nestedObject[attr.nodeName]=attr.nodeValue;}
}
else {Web.TypeDescriptor.initializeInstance(nestedObject,childNode,markupContext);}
}
else {propertyValue =null;if (propertyType ==String){propertyValue =childNode.text;}
else if (childNode.childNodes.length !=0){var valueNode;for (var childNodeIndex =0;childNodeIndex <childNode.childNodes.length;childNodeIndex++){if (childNode.childNodes[childNodeIndex].nodeType !=1){continue;}
valueNode =childNode.childNodes[childNodeIndex];break;}
if (valueNode){propertyValue =Web.TypeDescriptor.processMarkupNode(valueNode,markupContext);}
}
if (propertyValue){setter =instance['set_'+propertyName];setter.call(instance,propertyValue);}
}
}
else {eventInfo =events[nodeName];if (eventInfo &&eventInfo.actions){var actions =Web.TypeDescriptor.processMarkupNodes(childNode.childNodes,markupContext);if (actions.length){eventValue =instance[eventInfo.name];for (var e =0;e <actions.length;e++){eventValue.addAction(actions[e]);}
}
}
}
}
}
if (supportsBatchedUpdates){markupContext.addEndUpdate(instance);}
return instance;}
Web.TypeDescriptor.processMarkupNode =function(node,markupContext){var parsedObject =null;var tagPrefix =node.prefix;if (!tagPrefix ||(tagPrefix.length ==0)){tagPrefix ='script';}
var tagName =node.baseName;var tagType =Web.TypeDescriptor.getType(tagPrefix,tagName);if (tagType){var parseMethod =tagType.parseFromMarkup;if (!parseMethod){var baseType =tagType.getBaseType();while (baseType){parseMethod =baseType.parseFromMarkup;if (parseMethod){break;}
baseType =baseType.getBaseType();}
tagType.parseFromMarkup =parseMethod;}
if (parseMethod){parsedObject =parseMethod.call(null,tagType,node,markupContext);}
}
return parsedObject;}
Web.TypeDescriptor.processMarkupNodes =function(nodes,markupContext){var objects =[];for (var i =0;i <nodes.length;i++){var objectNode =nodes[i];if (objectNode.nodeType !=1){continue;}
var processedObject =this.processMarkupNode(objectNode,markupContext);if (processedObject){objects.add(processedObject);}
}
return objects;}
Web.TypeDescriptor.unload =function(){if (Web.TypeDescriptor._registeredTags){Web.TypeDescriptor._registeredTags =null;}
}
Web.TypeDescriptor.getAttribute =function(instance,attributeName){var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (!td){return null;}
return td._getAttributes()[attributeName];}
Web.TypeDescriptor.getProperty =function(instance,propertyName,key){if (Web.ICustomTypeDescriptor.isImplementedBy(instance)){return instance.getProperty(propertyName,key);}
if ((propertyName ==null)||(propertyName.length ==0)){return instance;}
var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (!td){return null;}
var propertyInfo =td._getProperties()[propertyName];if (!propertyInfo){return null;}
var getter =instance['get_'+propertyInfo.name];var object =getter.call(instance);if ((propertyInfo.type ==Object)&&propertyInfo.isReadOnly &&key){object =object[key];}
return object;}
Web.TypeDescriptor.setProperty =function(instance,propertyName,value,key){if (Web.ICustomTypeDescriptor.isImplementedBy(instance)){instance.setProperty(propertyName,value,key);return;}
var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (td){var propertyInfo =td._getProperties()[propertyName];if (propertyInfo){if (!propertyInfo.isReadOnly){if ((propertyInfo.type !=String)&&(typeof(value)=='string')&&propertyInfo.type.parse){value =propertyInfo.type.parse(value);}
var setter =instance['set_'+propertyInfo.name];setter.call(instance,value);}
else if ((propertyInfo.type ==Object)&&key){var getter =instance['get_'+propertyInfo.name];var object =getter.call(instance);object[key]=value;}
}
}
}
Web.TypeDescriptor.invokeMethod =function(instance,methodName,parameters){if (Web.ICustomTypeDescriptor.isImplementedBy(instance)){return instance.invokeMethod(methodName,parameters);}
var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (td){var methodInfo =td._getMethods()[methodName];if (methodInfo){var method =instance[methodInfo.name];if (!methodInfo.parameters ||!methodInfo.parameters.length){return method.call(instance);}
else {if (!parameters){return null;}
var arguments =[];for (var i =0;i <methodInfo.parameters.length;i++){var parameterInfo =methodInfo.parameters[i];var value =parameters[parameterInfo.name];if (value &&(parameterInfo.type !=String)&&(typeof(value)=='string')){value =parameterInfo.type.parse(value);}
arguments[i]=value;}
return method.apply(instance,arguments);}
}
}
return null;}
Web.TypeDescriptor.getPropertyType =function(instance,propertyName,key){if (Web.ICustomTypeDescriptor.isImplementedBy(instance)){return Object;}
if (key){return Object;}
var td =Web.TypeDescriptor.getTypeDescriptor(instance);if (!td){return null;}
var propertyInfo =td._getProperties()[propertyName];if (!propertyInfo){return null;}
return propertyInfo.type;}
Web.TypeDescriptor.MarkupContext =function(document,global,parentContext,dataContext){var _document =document;var _global =global;var _parentContext =parentContext;var _dataContext =dataContext;var _dataContextHidden;var _objects ={};var _pendingReferences =[];var _pendingEndUpdates =[];this.get_dataContext =function(){if (_dataContextHidden){return null;}
return _dataContext;}
this.get_document =function(){return _document;}
this.get_isGlobal =function(){return _global;}
this.addObject =function(id,object){_objects[id]=object;}
this.addEndUpdate =function(instance){_pendingEndUpdates.add(instance);}
this.addReference =function(instance,propertyInfo,reference){_pendingReferences.add({o:instance,p:propertyInfo,r:reference });}
this.complete =function(){_document =null;_dataContext =null;var i;for (i =0;i <_pendingReferences.length;i++){var pendingReference =_pendingReferences[i];var instance =pendingReference.o;var propertyInfo =pendingReference.p;var propertyValue =pendingReference.r;var object =this.findObject(propertyValue,false);if (object){var setter =instance['set_'+propertyInfo.name];setter.call(instance,object);}
}
_pendingReferences =null;for (i =0;i <_pendingEndUpdates.length;i++){_pendingEndUpdates[i].endUpdate();}
_pendingEndUpdates =null;}
this.dispose =function(){if (!_global){for (var o in _objects){if (Web.IDisposable.isImplementedBy(_objects[o])){_objects[o].dispose();}
_objects[o]=null;}
}
_document =null;_objects =null;_parentContext =null;_dataContext =null;}
this.findObject =function(id,elementsOnly){var object;if (elementsOnly){if (_document){object =_document.getElementById(id);}
if (!object &&_parentContext){object =_parentContext.findObject(id,elementsOnly);}
return object;}
object =_objects[id];if (!object &&_document){object =_document.getElementById(id);}
if (!object &&_parentContext){object =_parentContext.findObject(id,elementsOnly);}
return object;}
this.hideDataContext =function(){if (!_dataContextHidden){_dataContextHidden =true;return true;}
return false;}
this._reopen =function(){debug.assert(_global);_document =document;_pendingReferences =[];_pendingEndUpdates =[];}
this.restoreDataContext =function(){_dataContextHidden =false;}
}
Web.ISupportBatchedUpdates =function(){this.beginUpdate =Function.abstractMethod;this.endUpdate =Function.abstractMethod;}
Type.registerInterface('Web.ISupportBatchedUpdates');Web.ICustomTypeDescriptor =function(){this.getProperty =Function.abstractMethod;this.setProperty =Function.abstractMethod;this.invokeMethod =Function.abstractMethod;}
Type.registerInterface('Web.ICustomTypeDescriptor');Web.ITypeDescriptorProvider =function(){this.getDescriptor =Function.abstractMethod;}
Type.registerInterface('Web.ITypeDescriptorProvider');Web.ActionSequence =Web.Enum.create('BeforeEventHandler','AfterEventHandler');Web.IAction =function(){this.get_sequence =Function.abstractMethod;this.execute =Function.abstractMethod;this.setOwner =Function.abstractMethod;}
Type.registerInterface('Web.IAction');Web.Event =function(owner,autoInvoke){var _owner =owner;var _handlers =null;var _actions =null;var _autoInvoke =autoInvoke;var _invoked =false;this.get_autoInvoke =function(){return _autoInvoke;}
this._getActions =function(){if (_actions ==null){_actions =Web.Component.createCollection(_owner);}
return _actions;}
this._getHandlers =function(){if (_handlers ==null){_handlers =[];}
return _handlers;}
this._getOwner =function(){return _owner;}
this.isActive =function(){return ((_handlers !=null)&&(_handlers.length !=0))||((_actions !=null)&&(_actions.length !=0));}
this.get_isInvoked =function(){return _isInvoked;}
this.dispose =function(){if (_handlers){for (var h =_handlers.length -1;h >=0;h--){_handlers[h]=null;}
_handlers =null;}
if (_actions){_actions.dispose();_actions =null;}
_owner =null;}
this._setInvoked =function(value){_invoked =true;}
}
Type.registerSealedClass('Web.Event',null,Web.IDisposable);Web.Event.prototype.add =function(handler){this._getHandlers().add(handler);if (this.get_autoInvoke()&&this.get_isInvoked()){handler(this._getOwner(),Web.EventArgs.Empty);}
}
Web.Event.prototype.addAction =function(action){this._getActions().add(action);if (this.get_autoInvoke()&&this.get_isInvoked()){action.execute(this._getOwner(),Web.EventArgs.Empty);}
}
Web.Event.prototype.remove =function(handler){this._getHandlers().remove(handler);}
Web.Event.prototype.removeAction =function(action){this._getActions().remove(action);}
Web.Event.prototype.invoke =function(sender,eventArgs){if (this.isActive()){var actions =this._getActions();var handlers =this._getHandlers();var hasPostActions =false;var i;for (i =0;i <actions.length;i++){if (actions[i].get_sequence()==Web.ActionSequence.BeforeEventHandler){actions[i].execute(sender,eventArgs);}
else {hasPostActions =true;}
}
for (i =0;i <handlers.length;i++){handlers[i](sender,eventArgs);}
if (hasPostActions){for (i =0;i <actions.length;i++){if (actions[i].get_sequence()==Web.ActionSequence.AfterEventHandler){actions[i].execute(sender,eventArgs);}
}
}
this._setInvoked();}
}
Web.EventArgs =function(){this.getDescriptor =function(){var td =new Web.TypeDescriptor();return td;}
Web.EventArgs.registerBaseMethod(this,'getDescriptor');}
Type.registerClass('Web.EventArgs',null,Web.ITypeDescriptorProvider);Web.EventArgs.Empty =new Web.EventArgs();Web.CancelEventArgs =function(){Web.CancelEventArgs.initializeBase(this);var _canceled =false;this.get_canceled =function(){return _canceled;}
this.set_canceled =function(value){_canceled =value;}
this.getDescriptor =function(){var td =Web.CancelEventArgs.callBaseMethod(this,'getDescriptor');td.addProperty('canceled',Boolean);return td;}
Web.CancelEventArgs.registerBaseMethod(this,'getDescriptor');}
Type.registerClass('Web.CancelEventArgs',Web.EventArgs);Web.ApplicationType =Web.Enum.create('Other','InternetExplorer','Firefox');Web._Application =function(){var _references;var _currentLoadingReference;var _components;var _markupContext;var _disposableObjects;var _unloading;var _type;window.attachEvent('onload',onWindowLoad);window.attachEvent('onunload',onWindowUnload);this.get_type =function(){if (!_type){_type =Web.ApplicationType.Other;if (navigator.userAgent.indexOf('MSIE')!=-1){_type =Web.ApplicationType.InternetExplorer;}
else if (navigator.userAgent.indexOf('Firefox')!=-1){_type =Web.ApplicationType.Firefox;}
}
return _type;}
this.get_userAgent =function(){return navigator.userAgent;}
this.load =new Web.Event(this);this.unload =new Web.Event(this);this.dispose =function(){}
this.findObject =function(id){if (_markupContext){return _markupContext.findObject(id,false);}
return null;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addEvent('load',true);td.addEvent('unload',true);return td;}
this.getProperty =function(name,key){}
this.getService =function(serviceType){return null;}
this._initialize =function(){_references =[];_components =[];var atlasScripts =[];var scriptElements =document.getElementsByTagName('script');for (var e =0;e <scriptElements.length;e++){if (scriptElements[e].type =='text/xml-script'){atlasScripts.add(scriptElements[e]);}
}
if (!atlasScripts.length){onLoad();return;}
for (var s =0;s <atlasScripts.length;s++){var atlasScript =atlasScripts[s];var scriptMarkup =atlasScript.text ?atlasScript.text :atlasScript.innerHTML;if (scriptMarkup.startsWith('<!--')){var startIndex =scriptMarkup.indexOf('<',1);var endIndex =scriptMarkup.lastIndexOf('>');endIndex =scriptMarkup.lastIndexOf('>',endIndex -1);scriptMarkup =scriptMarkup.substring(startIndex,endIndex +1);}
var scriptDOM =new XMLDOM(scriptMarkup);var scriptDocumentNode =scriptDOM.childNodes[0];var scriptDocumentItemNodes =scriptDocumentNode.childNodes;for (var i =scriptDocumentItemNodes.length -1;i >=0;i--){var node =scriptDocumentItemNodes[i];if (node.nodeType !=1){continue;}
if (node.baseName =='components'){for (var c =0;c <node.childNodes.length;c++){var componentNode =node.childNodes[c];if (componentNode.nodeType !=1){continue;}
_components.add(componentNode);}
}
else if (node.baseName =='references'){for (var r =0;r <node.childNodes.length;r++){var referenceNode =node.childNodes[r];if (referenceNode.nodeType !=1){continue;}
if (referenceNode.baseName =='add'){var srcAttribute =referenceNode.attributes.getNamedItem('src');if (srcAttribute){_references.queue(srcAttribute.nodeValue);}
}
}
}
}
}
if (_references &&_references.length){loadReferences();}
else {loadObjects();}
}
this.invokeMethod =function(methodName,parameters){var method =Function.parse(methodName);if (typeof(method)=='function'){method();}
}
this.registerDisposableObject =function(object){if (!_disposableObjects){_disposableObjects =[];}
_disposableObjects.add(object);}
this.unregisterDisposableObject =function(object){if (!_unloading &&_disposableObjects){_disposableObjects.remove(object);}
}
this.requiresReference =function(scriptPath){}
this.setProperty =function(name,value,key){}
function loadObjects(){_markupContext =new Web.TypeDescriptor.MarkupContext(document,true);if (_components &&_components.length){Web.TypeDescriptor.processMarkupNodes(_components,_markupContext);_components =null;}
_markupContext.complete();onLoad();}
function loadReferences(){if (_currentLoadingReference){if ((_currentLoadingReference.readyState !='loaded')&&(_currentLoadingReference.readyState !='complete')){return;}
else {if (Web.Application.get_type()!=Web.ApplicationType.InternetExplorer){_currentLoadingReference.onload =null;}
else {_currentLoadingReference.onreadystatechange =null;}
_currentLoadingReference =null;}
}
if (_references &&_references.length){var reference =_references.dequeue();var scriptElement =document.createElement('script');_currentLoadingReference =scriptElement;if (Web.Application.get_type()!=Web.ApplicationType.InternetExplorer){scriptElement.readyState ='loaded';scriptElement.onload =loadReferences;}
else {scriptElement.onreadystatechange =loadReferences;}
scriptElement.type ='text/javascript';scriptElement.src =reference;var headElement =document.getElementsByTagName('head')[0];headElement.appendChild(scriptElement);return;}
loadObjects();}
function onLoad(){Web.Application.load.invoke(Web.Application,Web.EventArgs.Empty);var pageLoadHandler =Function.parse('pageLoad');if (typeof(pageLoadHandler)=='function'){pageLoadHandler();}
}
function onWindowLoad(){window.detachEvent('onload',onWindowLoad);Web.Application._initialize();}
function onWindowUnload(){window.detachEvent('onunload',onWindowUnload);Web.Application.unload.invoke(Web.Application,Web.EventArgs.Empty);var pageUnloadHandler =Function.parse('pageUnload');if (typeof(pageUnloadHandler)=='function'){pageUnloadHandler();}
if (_disposableObjects){_unloading =true;var count =_disposableObjects.length;for (var i =0;i <count;i++){_disposableObjects[i].dispose();}
_disposableObjects.clear();_disposableObjects =null;}
if (_markupContext){_markupContext.dispose();_markupContext =null;}
Web.TypeDescriptor.unload();}
this._update =function(scriptDocumentNode){var scriptDocumentItemNodes =scriptDocumentNode.childNodes;var referencesNode;var node;for (var i =scriptDocumentItemNodes.length -1;i >=0;i--){node =scriptDocumentItemNodes[i];if (node.nodeType !=1){continue;}
if (node.baseName =='components'){if (!_markupContext){_markupContext =new Web.TypeDescriptor.MarkupContext(document,true);}
else {_markupContext._reopen();}
Web.TypeDescriptor.processMarkupNodes(node.childNodes,_markupContext);_markupContext.complete();break;}
}
}
}
Type.registerSealedClass('Web._Application',null,Web.IDisposable,Web.ITypeDescriptorProvider,Web.ICustomTypeDescriptor);Web.TypeDescriptor.addType('script','application',Web._Application);Web._Application.parseFromMarkup =function(type,node,markupContext){if (!markupContext.get_isGlobal()){return null;}
Web.TypeDescriptor.initializeInstance(Web.Application,node,markupContext);return Web.Application;}
Web.Application =new Web._Application();Web.INotifyPropertyChanged =function(){this.propertyChanged =null;}
Type.registerInterface('Web.INotifyPropertyChanged');Web.INotifyCollectionChanged =function(){this.collectionChanged =null;}
Type.registerInterface('Web.INotifyCollectionChanged');Web.PropertyChangedEventArgs =function(propertyName){Web.PropertyChangedEventArgs.initializeBase(this);var _propertyName =propertyName;this.get_propertyName =function(){return _propertyName;}
this.getDescriptor =function(){var td =Web.PropertyChangedEventArgs.callBaseMethod(this,'getDescriptor');td.addProperty('propertyName',String,true);return td;}
}
Type.registerSealedClass('Web.PropertyChangedEventArgs',Web.EventArgs);Web.NotifyCollectionChangedAction =Web.Enum.create('Add','Remove','Reset');Web.CollectionChangedEventArgs =function(action,changedItem){Web.CollectionChangedEventArgs.initializeBase(this);var _action =action;var _changedItem =changedItem;this.get_action =function(){return _action;}
this.get_changedItem =function(){return _changedItem;}
this.getDescriptor =function(){var td =Web.CollectionChangedEventArgs.callBaseMethod(this,'getDescriptor');td.addProperty('action',Web.NotifyCollectionChangedAction,true);td.addProperty('changedItem',Object,true);return td;}
}
Type.registerSealedClass('Web.CollectionChangedEventArgs',Web.EventArgs);Web.BindingDirection =Web.Enum.create('In','Out','InOut');Web.BindingEventArgs =function(value,direction,targetPropertyType,transformerArgument){Web.BindingEventArgs.initializeBase(this);var _value =value;var _direction =direction;var _targetPropertyType =targetPropertyType;var _transformerArgument =transformerArgument;this.get_direction =function(){return _direction;}
this.get_targetPropertyType =function(){return _targetPropertyType;}
this.get_transformerArgument =function(){return _transformerArgument;}
this.get_value =function(){return _value;}
this.set_value =function(value){_value =value;}
this.getDescriptor =function(){var td =Web.BindingEventArgs.callBaseMethod(this,'getDescriptor');td.addProperty('direction',Web.BindingDirection,true);td.addProperty('targetPropertyType',Object,true);td.addProperty('transformerArgument',Object,true);td.addProperty('value',Object);return td;}
Web.BindingEventArgs.registerBaseMethod(this,'getDescriptor');}
Type.registerSealedClass('Web.BindingEventArgs',Web.CancelEventArgs);Web.Binding =function(){Web.Binding.initializeBase(this);var _id;var _component;var _componentNotificationHandler;var _dataContext;var _dataContextInUse;var _dataContextNotificationHandler;var _dataPath;var _dataPathParts;var _direction =Web.BindingDirection.In;var _property;var _propertyKey;var _automatic =true;var _transformerArgument =null;this.get_automatic =function(){return _automatic;}
this.set_automatic =function(value){if (!_dataContextInUse){_automatic =value;}
}
this.get_dataContext =function(){return _dataContext;}
this.set_dataContext =function(value){if (!_dataContextInUse){_dataContext =value;}
}
this.get_dataPath =function(){return _dataPath;}
this.set_dataPath =function(value){if (!_dataContextInUse){_dataPath =value;}
}
this.get_direction =function(){return _direction;}
this.set_direction =function(value){if (!_dataContextInUse){_direction =value;}
}
this.get_id =function(){return _id;}
this.set_id =function(value){_id =value;}
this.get_property =function(){return _property;}
this.set_property =function(value){if (!_dataContextInUse){_property =value;}
}
this.get_propertyKey =function(){return _propertyKey;}
this.set_propertyKey =function(value){if (!_dataContextInUse){_propertyKey =value;}
}
this.get_transformerArgument =function(){return _transformerArgument;}
this.set_transformerArgument =function(value){_transformerArgument =value;}
this.transform =new Web.Event(null);this.dispose =function(){this.transform.dispose();if (_componentNotificationHandler){_component.propertyChanged.remove(_componentNotificationHandler);_componentNotificationHandler =null;}
if (_dataContextNotificationHandler){if (Web.INotifyPropertyChanged.isImplementedBy(_dataContextInUse)){_dataContextInUse.propertyChanged.remove(_dataContextNotificationHandler);}
_dataContextNotificationHandler =null;}
_dataContextInUse =null;_dataContext =null;_component =null;}
this.evaluate =function(direction){if (direction ==Web.BindingDirection.In){this.evaluateIn();}
else {this.evaluateOut();}
}
this.evaluateDataPath =function(){var object =_dataContextInUse;for (var i =0;i <_dataPathParts.length -1;i++){object =Web.TypeDescriptor.getProperty(object,_dataPathParts[i]);if (!object){return null;}
}
return object;}
this.evaluateIn =function(){if (!_dataContextInUse){return;}
if ((_direction ==Web.BindingDirection.In)||(_direction ==Web.BindingDirection.InOut)){var propertyObject =_dataContextInUse;var propertyName =_dataPath;if (_dataPathParts){propertyObject =this.evaluateDataPath();if (propertyObject ==null){return;}
propertyName =_dataPathParts[_dataPathParts.length -1];}
var value =Web.TypeDescriptor.getProperty(propertyObject,propertyName);var canceled =false;if (this.transform.isActive()){var targetPropertyType =Web.TypeDescriptor.getPropertyType(_component,_property,_propertyKey);var be =new Web.BindingEventArgs(value,Web.BindingDirection.In,targetPropertyType,_transformerArgument);this.transform.invoke(this,be);canceled =be.get_canceled();value =be.get_value();}
if (!canceled){Web.TypeDescriptor.setProperty(_component,_property,value,_propertyKey);}
}
}
this.evaluateOut =function(){if (!_dataContextInUse){return;}
if ((_direction ==Web.BindingDirection.InOut)||(_direction ==Web.BindingDirection.Out)){var value =Web.TypeDescriptor.getProperty(_component,_property,_propertyKey);var canceled =false;var propertyObject =_dataContextInUse;var propertyName =_dataPath;if (_dataPathParts){propertyObject =this.evaluateDataPath();propertyName =_dataPathParts[_dataPathParts.length -1];}
if (this.transform.isActive()){var targetPropertyType =Web.TypeDescriptor.getPropertyType(propertyObject,propertyName);var be =new Web.BindingEventArgs(value,Web.BindingDirection.Out,targetPropertyType,_transformerArgument);this.transform.invoke(this,be);canceled =be.get_canceled();value =be.get_value();}
if (!canceled){Web.TypeDescriptor.setProperty(propertyObject,propertyName,value);}
}
}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('automatic',Boolean);td.addProperty('dataContext',Object);td.addProperty('dataPath',String);td.addProperty('direction',Web.BindingDirection);td.addProperty('id',String);td.addProperty('property',String);td.addProperty('propertyKey',String);td.addProperty('transformerArgument',String);td.addEvent('transform',false);td.addMethod('evaluateIn');td.addMethod('evaluateOut');return td;}
this.initialize =function(component){_component =component;_dataContextInUse =_dataContext;if (!_dataContextInUse){_dataContextInUse =_component.get_dataContext();}
if (_dataPath &&_dataPath.indexOf('.')>0){_dataPathParts =_dataPath.split('.');}
if (_automatic){if (Web.INotifyPropertyChanged.isImplementedBy(_component)){_componentNotificationHandler =Function.createDelegate(this,this._onComponentPropertyChanged);_component.propertyChanged.add(_componentNotificationHandler);}
if (_dataContextInUse &&Web.INotifyPropertyChanged.isImplementedBy(_dataContextInUse)){_dataContextNotificationHandler =Function.createDelegate(this,this._onDataContextPropertyChanged);_dataContextInUse.propertyChanged.add(_dataContextNotificationHandler);}
this.evaluate(Web.BindingDirection.In);}
}
this._onComponentPropertyChanged =function(sender,eventArgs){var propertyName =eventArgs.get_propertyName();if (!propertyName ||(propertyName ==_property)){this.evaluate(Web.BindingDirection.Out);}
}
this._onDataContextPropertyChanged =function(sender,eventArgs){var compareProperty =_dataPath;if (_dataPathParts){compareProperty =_dataPathParts[0];}
var propertyName =eventArgs.get_propertyName();if (!propertyName ||(propertyName ==compareProperty)){this.evaluate(Web.BindingDirection.In);}
}
}
Type.registerSealedClass('Web.Binding',null,Web.IDisposable,Web.ITypeDescriptorProvider);Web.TypeDescriptor.addType('script','binding',Web.Binding);Web.Binding.parseFromMarkup =function(type,node,markupContext){var newBinding =new Web.Binding();var builtInTransform;var transformAttribute =node.attributes.getNamedItem('transform');if (transformAttribute){var transformValue =transformAttribute.nodeValue;builtInTransform =Web.Binding.Transformers[transformValue];}
if (builtInTransform){newBinding.transform.add(builtInTransform);node.attributes.removeNamedItem('transform');}
var binding =Web.TypeDescriptor.initializeInstance(newBinding,node,markupContext);if (builtInTransform){node.attributes.setNamedItem(transformAttribute)}
if (binding){if (binding.get_id()){markupContext.addObject(binding.get_id(),binding);}
return binding;}
else {newBinding.dispose();}
return null;}
Web.Binding.Transformers ={};Web.Binding.Transformers.Invert =function(sender,eventArgs){eventArgs.set_value(!eventArgs.get_value());}
Web.Binding.Transformers.ToString =function(sender,eventArgs){var value =eventArgs.get_value();var newValue ='';var formatString =eventArgs.get_transformerArgument();var placeHolder =(formatString &&(formatString.length !=0))?formatString.indexOf('{0}'):-1;if (eventArgs.get_direction()==Web.BindingDirection.In){if (placeHolder !=-1){newValue =String.format(formatString,value);}
else if (value){newValue =value.toString();}
else {newValue =formatString;}
}
else {if (placeHolder !=-1){value =value.substr(placeHolder,3 +value.length -formatString.length);}
else if (formatString ==value){value =null;}
var propertyType =eventArgs.get_targetPropertyType();if (!value){if (propertyType ==Boolean){newValue =false;}
else if (propertyType ==Number){newValue =0;}
else if (propertyType ==String){newValue ='';}
else {newValue =null;}
}
else {newValue =propertyType.parse(value);}
}
eventArgs.set_value(newValue);}
Web.Binding.Transformers.Add =function(sender,eventArgs){var value =eventArgs.get_value();if (typeof(value)!='number'){value =Number.parse(value);}
var delta =eventArgs.get_transformerArgument();if (!delta){delta =1;}
if (typeof(delta)!='number'){delta =Number.parse(delta);}
if (eventArgs.get_direction()==Web.BindingDirection.Out){delta =-delta;}
var newValue =value +delta;if (eventArgs.get_targetPropertyType()!='number'){newValue =newValue.toString();}
eventArgs.set_value(newValue);}
Web.Binding.Transformers.Multiply =function(sender,eventArgs){var value =eventArgs.get_value();if (typeof(value)!='number'){value =Number.parse(value);}
var factor =eventArgs.get_transformerArgument();if (!factor){factor =1;}
if (typeof(factor)!='number'){factor =Number.parse(factor);}
var newValue;if (eventArgs.get_direction()==Web.BindingDirection.Out){newValue =value /factor;}
else {newValue =value *factor;}
if (eventArgs.get_targetPropertyType()!='number'){newValue =newValue.toString();}
eventArgs.set_value(newValue);}
Web.Binding.Transformers.Compare =function(sender,eventArgs){var value =eventArgs.get_value();var compareValue =eventArgs.get_transformerArgument();if (compareValue ==null){value =value ?true :false;}
else {value =(value ==compareValue);}
eventArgs.set_value(value);}
Web.Binding.Transformers.CompareInverted =function(sender,eventArgs){var value =eventArgs.get_value();var compareValue =eventArgs.get_transformerArgument();if (compareValue ==null){value =value ?false :true;}
else {value =(value !=compareValue);}
eventArgs.set_value(value);}
Web.Component =function(registerAsDisposable){var _id =null;var _initialized =false;var _updating =false;var _bindings =null;var _dataContext =null;var _events =[];if (registerAsDisposable){Web.Application.registerDisposableObject(this);}
this.get_bindings =function(){if (!_bindings){_bindings =[];}
return _bindings;}
this.get_dataContext =function(){return _dataContext;}
Web.Component.registerBaseMethod(this,'get_dataContext');this.set_dataContext =function(value){_dataContext =value;}
this.get_id =function(){return _id;}
this.set_id =function(value){_id =value;}
this.get_isInitialized =function(){return _initialized;}
this.get_isUpdating =function(){return _updating;}
this.createEvent =function(autoInvoke){var eventObject =new Web.Event(this,autoInvoke);_events.add(eventObject);return eventObject;}
this.propertyChanged =this.createEvent();this.beginUpdate =function(){_updating =true;}
this.dispose =function(){if (_bindings){for (var i =0;i <_bindings.length;i++){_bindings[i].dispose();_bindings[i]=null;}
_bindings =null;}
if (_events){for (var e =_events.length -1;e >=0;e--){_events[e].dispose();_events[e]=null;}
_events =null;}
Web.Application.unregisterDisposableObject(this);}
Web.Component.registerBaseMethod(this,'dispose');this.endUpdate =function(){_updating =false;if (!_initialized){this.initialize();}
this.updated();}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('bindings',Array,true);td.addProperty('dataContext',Object);td.addProperty('id',String);td.addEvent('propertyChanged',true);return td;}
Web.Component.registerBaseMethod(this,'getDescriptor');this.initialize =function(){if (_bindings){for (var i =0;i <_bindings.length;i++){_bindings[i].initialize(this);}
}
_initialized =true;}
Web.Component.registerBaseMethod(this,'initialize');this.raisePropertyChanged =function(propertyName){this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs(propertyName));}
Web.Component.registerBaseMethod(this,'raisePropertyChanged');this.updated =function(){}
Web.Component.registerBaseMethod(this,'updated');}
Type.registerAbstractClass('Web.Component',null,Web.IDisposable,Web.ITypeDescriptorProvider,Web.ISupportBatchedUpdates,Web.INotifyPropertyChanged);Web.Component.parseFromMarkup =function(type,node,markupContext){var newComponent =Type.createInstance(type);var dataContextHidden =false;var dataContext =markupContext.get_dataContext();if (dataContext){dataContextHidden =markupContext.hideDataContext();}
var component =Web.TypeDescriptor.initializeInstance(newComponent,node,markupContext);if (component){if (component.get_id()){markupContext.addObject(component.get_id(),component);}
if (dataContext){component.set_dataContext(dataContext);}
}
else {newComponent.dispose();}
if (dataContextHidden){markupContext.restoreDataContext();}
return component;}
Web.Component.createCollection =function(component){var collection =[];collection._component =component;collection.collectionChanged =new Web.Event(null);collection._add =collection.add;collection.add =function(item){this._add(item);item.setOwner(this._component);this.collectionChanged.invoke(this,new Web.CollectionChangedEventArgs(Web.NotifyCollectionChangedAction.Add,item));}
collection._clear =collection.clear;collection.clear =function(){for (var i =this.length -1;i >=0;i--){this[i].dispose();this[i]=null;}
this._clear();this.collectionChanged.invoke(this,new Web.CollectionChangedEventArgs(Web.NotifyCollectionChangedAction.Reset,null));}
collection.dispose =function(){this.clear();this._component =null;}
collection._remove =collection.remove;collection.remove =function(item){item.dispose();this._remove(item);this.collectionChanged.invoke(this,new Web.CollectionChangedEventArgs(Web.NotifyCollectionChangedAction.Remove,item));}
collection._removeAt =collection.removeAt;collection.removeAt =function(index){var item =this[index];item.dispose();this._removeAt(index);this.collectionChanged.invoke(this,new Web.CollectionChangedEventArgs(Web.NotifyCollectionChangedAction.Remove,item));}
return collection;}
Web.Reference =function(){var _component;this.get_component =function(){return _component;}
this.set_component =function(value){_component =value;}
this.dispose =function(){_component =null;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('component',Object);return td;}
}
Type.registerSealedClass('Web.Reference',null,Web.ITypeDescriptorProvider,Web.IDisposable);Web.TypeDescriptor.addType('script','reference',Web.Reference);Web.Reference.parseFromMarkup =function(type,node,markupContext){var newReference =new Web.Reference();var reference =Web.TypeDescriptor.initializeInstance(newReference,node,markupContext);if (reference){return reference;}
else {newReference.dispose();}
return null;}
Web.Action =function(){Web.Action.initializeBase(this,[false]);var _eventSource;var _eventArgs;var _result;var _target;var _sequence =Web.ActionSequence.BeforeEventHandler;this.get_dataContext =function(){return this;}
this.get_eventArgs =function(){return _eventArgs;}
this.get_result =function(){return _result;}
this.get_sequence =function(){return _sequence;}
this.set_sequence =function(value){_sequence =value;}
this.get_sender =function(){return _eventSource;}
this.get_target =function(){return _target;}
this.set_target =function(value){_target =value;}
this.dispose =function(){_target =null;_eventSource =null;Web.Action.callBaseMethod(this,'dispose');}
Web.Action.registerBaseMethod(this,'dispose');this.execute =function(sender,eventArgs){_eventArgs =eventArgs;var bindings =this.get_bindings();var i;for (i =0;i <bindings.length;i++){bindings[i].evaluateIn();}
_result =this.performAction();for (i =0;i <bindings.length;i++){bindings[i].evaluateOut();}
_eventArgs =null;_result =null;}
this.getDescriptor =function(){var td =Web.Action.callBaseMethod(this,'getDescriptor');td.addProperty('eventArgs',Web.EventArgs);td.addProperty('result',Object);td.addProperty('sender',Object);td.addProperty('sequence',Web.ActionSequence);td.addProperty('target',Object);return td;}
Web.Action.registerBaseMethod(this,'getDescriptor');this.initialize =function(){var bindings =this.get_bindings();for (var i =0;i <bindings.length;i++){bindings[i].set_automatic(false);}
Web.Action.callBaseMethod(this,'initialize');}
this.setOwner =function(eventSource){_eventSource =eventSource;}
}
Type.registerAbstractClass('Web.Action',Web.Component,Web.IAction);Web.Action.parseFromMarkup =function(type,node,markupContext){var newAction =Type.createInstance(type);var action =Web.TypeDescriptor.initializeInstance(newAction,node,markupContext);if (action){if (action.get_id()){markupContext.addObject(action.get_id(),action);}
return action;}
else {newAction.dispose();}
return null;}
Web.InvokeMethodAction =function(){Web.InvokeMethodAction.initializeBase(this);var _method;var _parameters;this.get_method =function(){return _method;}
this.set_method =function(value){_method =value;}
this.get_parameters =function(){if (!_parameters){_parameters ={};}
return _parameters;}
this.getDescriptor =function(){var td =Web.InvokeMethodAction.callBaseMethod(this,'getDescriptor');td.addProperty('method',String);td.addProperty('parameters',Object,true);return td;}
this.performAction =function(){return Web.TypeDescriptor.invokeMethod(this.get_target(),_method,_parameters);}
}
Type.registerSealedClass('Web.InvokeMethodAction',Web.Action);Web.TypeDescriptor.addType('script','invokeMethod',Web.InvokeMethodAction);Web.SetPropertyAction =function(){Web.SetPropertyAction.initializeBase(this);var _property;var _propertyKey;var _value;this.get_property =function(){return _property;}
this.set_property =function(value){_property =value;}
this.get_propertyKey =function(){return _propertyKey;}
this.set_propertyKey =function(value){_propertyKey =value;}
this.get_value =function(){return _value;}
this.set_value =function(value){_value =value;}
this.getDescriptor =function(){var td =Web.SetPropertyAction.callBaseMethod(this,'getDescriptor');td.addProperty('property',String);td.addProperty('propertyKey',String);td.addProperty('value',String);return td;}
this.performAction =function(){Web.TypeDescriptor.setProperty(this.get_target(),_property,_value,_propertyKey);return null;}
}
Type.registerSealedClass('Web.SetPropertyAction',Web.Action);Web.TypeDescriptor.addType('script','setProperty',Web.SetPropertyAction);Web.Timer =function(){Web.Timer.initializeBase(this,[true]);var _interval =1000;var _enabled;var _timer =null;this.getDescriptor =function(){var td =Web.Timer.callBaseMethod(this,'getDescriptor');td.addProperty('interval',Number);td.addProperty('enabled',Boolean);td.addEvent('tick',true);return td;}
this.get_interval =function(){return _interval;}
this.set_interval =function(value){if (_interval !=value){_interval =value;this.raisePropertyChanged('interval');if (!this.get_isUpdating()&&(_timer !=null)){stopTimer();startTimer(this);}
}
}
this.get_enabled =function(){return _enabled;}
this.set_enabled =function(value){if (value !=this.get_enabled()){_enabled =value;this.raisePropertyChanged('enabled');if (!this.get_isUpdating()){if (value){startTimer(this);}
else {stopTimer();}
}
}
}
this.tick =this.createEvent();this.dispose =function(){this.set_enabled(false);stopTimer();Web.Timer.callBaseMethod(this,'dispose');}
this.updated =function(){Web.Timer.callBaseMethod(this,'updated');if (_enabled){stopTimer();startTimer(this);}
}
function _timerCallback(context){context.tick.invoke(context,Web.EventArgs.Empty);}
function startTimer(instance){_timer =window.setInterval(Function.createCallback(_timerCallback,instance),_interval);}
function stopTimer(){window.clearInterval(_timer);_timer =null;}
}
Type.registerSealedClass('Web.Timer',Web.Component);Web.TypeDescriptor.addType('script','timer',Web.Timer);Web.Counter =function(){Web.Timer.initializeBase(this,[false]);var _value =0;var _lowerBound =Number.NaN;var _upperBound =Number.NaN;this.getDescriptor =function(){var td =Web.Counter.callBaseMethod(this,'getDescriptor');td.addProperty('value',Number);td.addProperty('lowerBound',Number);td.addProperty('upperBound',Number);td.addProperty('canDecrement',Boolean);td.addProperty('canIncrement',Boolean);td.addMethod('increment');td.addMethod('decrement');return td;}
this.get_canDecrement =function(){return isNaN(_lowerBound)||(_value >_lowerBound);}
this.get_canIncrement =function(){return isNaN(_upperBound)||(_value <_upperBound);}
this.get_lowerBound =function(){return _lowerBound;}
this.set_lowerBound =function(value){if ((isNaN(value)&&isNaN(_lowerBound))||(value ==_lowerBound))return;var oldCanDecrement =this.get_canDecrement();_lowerBound =value;this.raisePropertyChanged('lowerBound');if (oldCanDecrement !=this.get_canDecrement()){this.raisePropertyChanged('canDecrement');}
}
this.get_upperBound =function(){return _upperBound;}
this.set_upperBound =function(value){if ((isNaN(value)&&isNaN(_upperBound))||(value ==_upperBound))return;var oldCanIncrement =this.get_canIncrement();_upperBound =value;this.raisePropertyChanged('upperBound');if (oldCanIncrement !=this.get_canIncrement()){this.raisePropertyChanged('canIncrement');}
}
this.get_value =function(){return _value;}
this.set_value =function(value){if ((isNaN(_lowerBound)||(value >=_lowerBound))&&(isNaN(_upperBound)||(value <=_upperBound))&&(_value !=value)){var oldCanDecrement =this.get_canDecrement();var oldCanIncrement =this.get_canIncrement();_value =value;this.raisePropertyChanged('value');if (oldCanDecrement !=this.get_canDecrement()){this.raisePropertyChanged('canDecrement');}
if (oldCanIncrement !=this.get_canIncrement()){this.raisePropertyChanged('canIncrement');}
}
}
this.decrement =function(){this.set_value(_value -1);}
this.increment =function(){this.set_value(_value +1);}
}
Type.registerSealedClass('Web.Counter',Web.Component);Web.TypeDescriptor.addType('script','counter',Web.Counter);Type.registerNamespace('Web.Serialization');Web.Serialization.JSON =new function(){function serializeWithBuilder(object,stringBuilder){var i;switch (typeof object){case 'object':if (object){if (Array.isInstanceOfType(object)){stringBuilder.append('[');for (i =0;i <object.length;++i){if (i >0){stringBuilder.append(',');}
stringBuilder.append(serializeWithBuilder(object[i],stringBuilder));}
stringBuilder.append(']');} else {if (typeof object.serialize =='function'){stringBuilder.append(object.serialize());break;}
stringBuilder.append('{');var needComma =false;for (var name in object){if (name.startsWith('$')){continue;}
var value =object[name];if (typeof value !='undefined'&&typeof value !='function'){if (needComma){stringBuilder.append(',');}
else {needComma =true;}
stringBuilder.append(serializeWithBuilder(name,stringBuilder));stringBuilder.append(':');stringBuilder.append(serializeWithBuilder(value,stringBuilder));}
}
stringBuilder.append('}');}
}
else {stringBuilder.append('null');}
break;case 'number':if (isFinite(object)){stringBuilder.append(String(object));}
else {stringBuilder.append('null');}
break;case 'string':stringBuilder.append('"');var length =object.length;for (i =0;i <length;++i){var curChar =object.charAt(i);if (curChar >=' '){if (curChar =='\\'||curChar =='"'){stringBuilder.append('\\');}
stringBuilder.append(curChar);}
else {switch (curChar){case '\b':stringBuilder.append('\\b');break;case '\f':stringBuilder.append('\\f');break;case '\n':stringBuilder.append('\\n');break;case '\r':stringBuilder.append('\\r');break;case '\t':stringBuilder.append('\\t');break;default:stringBuilder.append('\\u00');stringBuilder.append(curChar.charCodeAt().toString(16));}
}
}
stringBuilder.append('"');break;case 'boolean':stringBuilder.append(object.toString());break;default:stringBuilder.append('null');break;}
}
this.serialize =function(object){var stringBuilder =new Web.StringBuilder();serializeWithBuilder(object,stringBuilder);return stringBuilder.toString();}
this.deserialize =function(data){return eval('('+data +')');}
}
Type.registerNamespace('Web.Net');Web.Net.WebResponse =function(requestor,userContext){var _requestor =requestor;var _userContext =userContext;var _resultObject;this.get_data =function(){return _requestor.responseText;}
this.get_object =function(){if (!_resultObject){var data =this.get_data();_resultObject =Web.Serialization.JSON.deserialize(data);}
return _resultObject;}
this.get_statusCode =function(){return _requestor.status;}
this.get_statusText =function(){return _requestor.statusText;}
this.get_userContext =function(){return _userContext;}
this.get_xml =function(){return _requestor.responseXML;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('data',String,true);td.addProperty('object',Object,true);td.addProperty('statusCode',Number,true);td.addProperty('statusText',String,true);td.addProperty('xml',Object,true);return td;}
}
Type.registerClass('Web.Net.WebResponse',null,Web.ITypeDescriptorProvider);Web.Net.WebRequest =function(){Web.Net.WebRequest.initializeBase(this,[true]);var _url =null;var _effectiveUrl;var _timeoutInterval =0;var _headers =null;var _body =null;var _userContext =null;var _requestor =null;var _timer =null;var _isComplete =true;var _timedOut =false;var _aborted =false;var _response;this.get_aborted =function(){return _aborted;}
this.get_isActive =function(){return !_isComplete;}
this.get_body =function(){return _body;}
this.set_body =function(value){_body =value;}
this.get_headers =function(){if (_headers ==null){_headers ={};}
return _headers;}
this.get_response =function(){if (_isComplete &&_requestor &&!_response){_response =new Web.Net.WebResponse(_requestor,_userContext);_requestor =null;}
return _response;}
Web.Net.WebRequest.registerBaseMethod(this,'get_response');this.get_timeoutInterval =function(){return _timeoutInterval;}
this.set_timeoutInterval =function(value){_timeoutInterval =value;}
this.get_timedOut =function(){return _timedOut;}
this.get_url =function(){return _url;}
this.set_url =function(value){if (!_effectiveUrl){_url =value;}
}
this.aborted =this.createEvent();this.completed =this.createEvent();this.timeout =this.createEvent();this.abort =function(){if (_timer !=null){window.clearTimeout(_timer);_timer =null;}
if (_requestor !=null){_requestor.onreadystatechange =Function.emptyMethod;_requestor.abort();if (_isComplete ==false){_aborted =true;_isComplete =true;this.raisePropertyChanged('isActive');this.aborted.invoke(this,Web.EventArgs.Empty);}
_requestor =null;}
_response =null;_userContext =null;}
Web.Net.WebRequest.registerBaseMethod(this,'abort');this.dispose =function(){if (this.completed){this.completed.dispose();this.completed =null;}
if (this.timeout){this.timeout.dispose();this.timeout =null;}
this.abort();Web.Net.WebRequest.callBaseMethod(this,'dispose');}
Web.Net.WebRequest.registerBaseMethod(this,'dispose');this.getDescriptor =function(){var td =Web.Net.WebRequest.callBaseMethod(this,'getDescriptor');td.addProperty('isActive',Boolean,true);td.addProperty('response',Web.Net.WebResponse,true);td.addProperty('url',String);td.addProperty('timeoutInterval',Number);td.addEvent('aborted',true);td.addEvent('completed',true);td.addEvent('timeout',true);td.addMethod('invoke');td.addMethod('abort');return td;}
Web.Net.WebRequest.registerBaseMethod(this,'getDescriptor');this.getEffectiveUrl =function(){return _url;}
Web.Net.WebRequest.registerBaseMethod(this,'getEffectiveUrl');this.invoke =function(userContext){if (_isComplete ==false){this.abort();}
_isComplete =false;_aborted =false;_timedOut =false;_response =null;_userContext =userContext;this.raisePropertyChanged('isActive');_requestor =new XMLHttpRequest();_requestor.onreadystatechange =Function.createCallback(onReadyStateChange,this);if (!_effectiveUrl){_effectiveUrl =this.getEffectiveUrl();}
if (_body !=null){_requestor.open('POST',_effectiveUrl,true);if ((_headers ==null)||!_headers['Content-Type']){_requestor.setRequestHeader('Content-Type','application/x-www-form-urlencoded');}
}
else {_requestor.open('GET',_effectiveUrl,true);}
if (_headers !=null){for (var header in _headers){_requestor.setRequestHeader(header,_headers[header]);}
}
if (_timeoutInterval !=0){_timer =window.setTimeout(Function.createCallback(onTimeout,this),_timeoutInterval);}
_requestor.send(_body);}
Web.Net.WebRequest.registerBaseMethod(this,'invoke');function onReadyStateChange(context){if (_requestor.readyState ==4){if (_timer !=null){window.clearTimeout(_timer);_timer =null;}
_isComplete =true;_requestor.onreadystatechange =Function.emptyMethod;context.raisePropertyChanged('isActive');context.completed.invoke(context,Web.EventArgs.Empty);_requestor =null;_userContext =null;}
}
function onTimeout(context){if (_isComplete ==false){if (_timer !=null){window.clearTimeout(_timer);_timer =null;}
_timedOut =true;_isComplete =true;_requestor.onreadystatechange =Function.emptyMethod;_requestor.abort();context.raisePropertyChanged('isActive');context.timeout.invoke(context,Web.EventArgs.Empty);_requestor =null;_userContext =null;}
}
}
Type.registerClass('Web.Net.WebRequest',Web.Component);Web.TypeDescriptor.addType('script','webRequest',Web.Net.WebRequest);Web.Net.WebRequest.createQueryString =function(queryString,encodeMethod){if (encodeMethod ==null)encodeMethod =encodeURIComponent;var sb =new Web.StringBuilder();var i =0;for (var arg in queryString){if (i !=0){sb.append('&');}
sb.append(arg);sb.append('=');sb.append(encodeMethod(queryString[arg]));i++;}
return sb.toString();}
Web.Net.WebRequest.createUrl =function(url,queryString){if (!queryString){return url;}
return url +'?'+Web.Net.WebRequest.createQueryString(queryString);}
Web.Net.MethodRequest =function(){Web.Net.MethodRequest.initializeBase(this);var _methodName =null;var _parameters =null;this.get_methodName =function(){return _methodName;}
this.set_methodName =function(value){_methodName =value;}
this.get_parameters =function(){if (_parameters ==null){_parameters ={};}
return _parameters;}
this.getDescriptor =function(){var td =Web.Net.MethodRequest.callBaseMethod(this,'getDescriptor');td.addProperty('methodName',String);td.addProperty('parameters',Object,true);return td;}
Web.Net.MethodRequest.registerBaseMethod(this,'getDescriptor');}
Type.registerAbstractClass('Web.Net.MethodRequest',Web.Net.WebRequest);Web.Net.MethodRequest.callMethod =function(request,methodName,params,onMethodComplete,onMethodTimeout,onMethodError,userContext){function onMethodCompleteInternal(sender,eventArgs){var response =sender.get_response();var statusCode =response.get_statusCode();var result =null;try {result =response.get_object();}
catch (ex){}
if (((statusCode <200)||(statusCode >=300))||Web.Net.MethodRequestError.isInstanceOfType(result)){if (onMethodError){onMethodError(result,response,userContext);}
}
else if (onMethodComplete){onMethodComplete(result,response,userContext);}
request.dispose();}
function onMethodTimeoutInternal(sender,eventArgs){onMethodTimeout(userContext);request.dispose();}
function onMethodErrorInternal(sender,eventArgs){onMethodError(sender.get_response(),userContext);request.dispose();}
request.set_methodName(methodName);if (onMethodComplete ||onMethodError){request.completed.add(onMethodCompleteInternal);}
if (onMethodTimeout){request.timeout.add(onMethodTimeoutInternal);}
if (params){var requestParams =request.get_parameters();for (var param in params){requestParams[param]=params[param];}
}
request.invoke(userContext);return request;}
Web.Net.MethodRequest.generateTypedConstructor =function(serverType){return function(properties){this.__serverType =serverType;if (properties !=null){for (var name in properties){this[name]=properties[name];}
}
}
}
Web.Net.MethodRequestError =function(message,stackTrace,exceptionType){var _message =message;var _stackTrace =stackTrace;var _exceptionType =exceptionType;this.get_message =function(){return _message;}
this.get_stackTrace =function(){return _stackTrace;}
this.get_exceptionType =function(){return _exceptionType;}
}
Type.registerClass('Web.Net.MethodRequestError',Web.Net.MethodRequestError);Web.Net.ServiceMethodRequest =function(){Web.Net.ServiceMethodRequest.initializeBase(this);this.getEffectiveUrl =function(){return Web.Net.WebRequest.createUrl(this.get_url(),{mn :this.get_methodName()} );}
this.invoke =function(userContext){this.set_body(Web.Serialization.JSON.serialize(this.get_parameters()));Web.Net.ServiceMethodRequest.callBaseMethod(this,'invoke',[userContext]);}
}
Type.registerClass('Web.Net.ServiceMethodRequest',Web.Net.MethodRequest);Web.TypeDescriptor.addType('script','serviceMethod',Web.Net.ServiceMethodRequest);Web.Net.ServiceMethodRequest.callMethod =function(methodURL,methodName,params,onMethodComplete,onMethodTimeout,onMethodError,userContext){var request =new Web.Net.ServiceMethodRequest();request.set_url(methodURL);return Web.Net.MethodRequest.callMethod(request,methodName,params,onMethodComplete,onMethodTimeout,onMethodError,userContext);}
Web.Net.ServiceMethodRequest.createProxyMethod =function(proxy,methodName){var numOfParams =arguments.length-2;var createWebMethodArguments =arguments;proxy[methodName]=function(){var args ={};for (var i=0;i<numOfParams;i++)args[createWebMethodArguments[i+2]]=arguments[i];var callMethodArgs =[proxy.path,methodName,args ];for (var i=0;i+numOfParams<arguments.length;i++)callMethodArgs[i+3]=arguments[numOfParams+i];return Web.Net.ServiceMethodRequest.callMethod.apply(null,callMethodArgs);}
}
Web.Net.PageMethodRequest =function(){Web.Net.PageMethodRequest.initializeBase(this);this.getEffectiveUrl =function(){var form =document.forms[0];return form.action;}
this.invoke =function(userContext){var form =document.forms[0];var bodyDictionary =new Object();bodyDictionary["__serviceMethodName"]=this.get_methodName();bodyDictionary["__serviceMethodParams"]=Web.Serialization.JSON.serialize(this.get_parameters());var count =form.elements.length;var element;for (var i =0;i <count;i++){element =form.elements[i];var tagName =element.tagName.toLowerCase();if (tagName =="input"){var type =element.type;if ((type =="text"||type =="hidden"||type =="password"||((type =="checkbox"||type =="radio")&&element.checked))){bodyDictionary[element.name]=element.value;}
}
else if (tagName =="select"){var selectCount =element.options.length;for (var j =0;j <selectCount;j++){var selectChild =element.options[j];if (selectChild.selected ==true){bodyDictionary[element.name]=element.value;}
}
}
else if (tagName =="textarea"){bodyDictionary[element.name]=element.value;}
}
this.set_body(Web.Net.WebRequest.createQueryString(bodyDictionary,encodeFormPostField));Web.Net.PageMethodRequest.callBaseMethod(this,'invoke',[userContext]);}
function encodeFormPostField(param){param =param.replace('%',"%25");param =param.replace('&',"%26");param =param.replace('=',"%3d");param =param.replace('+',"%2b");return param;}
}
Type.registerClass('Web.Net.PageMethodRequest',Web.Net.MethodRequest);Web.TypeDescriptor.addType('script','pageMethod',Web.Net.PageMethodRequest);Web.Net.PageMethodRequest.callMethod =function(methodName,params,onMethodComplete,onMethodTimeout,onMethodError,userContext){var request =new Web.Net.PageMethodRequest();return Web.Net.MethodRequest.callMethod(request,methodName,params,onMethodComplete,onMethodTimeout,onMethodError,userContext);}
Web.Net.PageMethodRequest.createProxyMethod =function(proxy,methodName){var numOfParams =arguments.length-2;var createWebMethodArguments =arguments;proxy[methodName]=function(){var args ={};for (var i=0;i<numOfParams;i++)args[createWebMethodArguments[i+2]]=arguments[i];var callMethodArgs =[methodName,args ];for (var i=0;i+numOfParams<arguments.length;i++)callMethodArgs[i+2]=arguments[numOfParams+i];return Web.Net.PageMethodRequest.callMethod.apply(null,callMethodArgs);}
}
Type.registerNamespace('Web.Data');Web.Data.DataColumn =function(columnName,dataType,defaultValue){var _columnName =columnName;var _dataType =dataType;var _defaultValue =defaultValue;this.get_columnName =function(){return _columnName;}
this.get_dataType =function(){return _dataType;}
this.get_defaultValue =function(){return _defaultValue;}
this.dispose =function(){_columnName =null;_dataType =null;_defaultValue =null;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('columnName',String,true);td.addProperty('dataType',Web.Type,true);td.addProperty('defaultValue',Object,true);return td;}
}
Type.registerSealedClass('Web.Data.DataColumn',null,Web.ITypeDescriptorProvider,Web.IDisposable);Web.Data.DataRow =function(objectDataRow,dataTableOwner,index){var _owner =dataTableOwner;var _row =objectDataRow;var _index =index;this.get__isDirty =function(){return typeof(_row._original)=="object";}
this.get__index =function(){return _index;}
this._set__index =function(index){_index =index;}
this.get__rowObject =function(){return _row;}
this.dispose =function(){if (this.propertyChanged){this.propertyChanged.dispose();}
_row =null;_owner =null;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('_isDirty',Boolean,true);td.addProperty('_index',Boolean,true);td.addProperty('_rowObject',Object,true);td.addEvent('propertyChanged',true);return td;}
this.initialize =function(){this.propertyChanged.initialize(this);}
this.propertyChanged =new Web.Event(null);this.getProperty =function(name,key){if (name =="_isDirty")return this.get__isDirty();if (name =="_index")return _index;if ((name ==null)||(name =="")||(name =="_rowObject")){return typeof(_row._rowObject)!="undefined"?_row._rowObject :_row;}
if (Web.ITypeDescriptorProvider.isImplementedBy(_row)){return Web.TypeDescriptor.getProperty(_row,name,key);}
return _row[name];}
this.setProperty =function(name,value,key){var keys =_owner ?_owner.get_keys():null;if ((keys &&keys.contains(name))||(_row[name]==value))return;var isDirty =this.get__isDirty();if (!isDirty &&_owner){var original ={};for (var columnName in _row){if ((columnName.charAt(0)!='_')&&(typeof(_row[columnName])!="function")){original[columnName]=_row[columnName];}
}
_row._original =original;}
if (Web.ITypeDescriptorProvider.isImplementedBy(_row)){Web.TypeDescriptor.setProperty(_row,name,value,key);}
else {_row[name]=value;}
this.raisePropertyChanged(name);if (!isDirty){this.raisePropertyChanged("_isDirty");}
if (_owner){_owner.raiseRowChanged(_row);}
}
this.invokeMethod =function(methodName,parameters){}
this.raisePropertyChanged =function(propertyName){this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs(propertyName));}
}
Type.registerSealedClass('Web.Data.DataRow',null,Web.ICustomTypeDescriptor,Web.INotifyPropertyChanged,Web.ITypeDescriptorProvider,Web.IDisposable);Web.Data.DataTable =function(tableArray,columns,keys){var _array =tableArray;if (!Array.isInstanceOfType(_array)){_array =[_array];}
var _columns =Array.isInstanceOfType(columns)?columns :[];var _keys =Array.isInstanceOfType(keys)?keys :[];var _rows =[];var _deletedRows =[];var _newRows =[];var _updatedRows =[];this.get_columns =function(){return _columns;}
this.get_keys =function(){return _keys;}
this.get_isDirty =function(){return (_deletedRows.length !=0)||(_newRows.length !=0)||(_updatedRows.length !=0);}
this.get_length =function(){return _array.length;}
this.add =function(rowObject){var row;if (Web.Data.DataRow.isInstanceOfType(rowObject)){row =rowObject;rowObject =rowObject.get__rowObject();}
else {row =new Web.Data.DataRow(rowObject,this);}
var index =_array.length;row._set__index(index);var columns =this.get_columns();if (columns){for(var i =columns.length -1;i >=0;i--){var column =columns[i];if (typeof(rowObject[column.get_columnName()])=="undefined"){rowObject[column.get_columnName()]=column.get_defaultValue();}
}
}
var oldIsDirty =this.get_isDirty();_array[index]=rowObject;_rows[index]=row;_newRows.add(rowObject);this.raiseCollectionChanged(Web.NotifyCollectionChangedAction.Add,row);this.raisePropertyChanged("length");if (!oldIsDirty){this.raisePropertyChanged("isDirty");}
return row;}
this.clear =function(){if (this.get_length()>0){var oldIsDirty =this.get_isDirty();for (var i =_array.length -1;i >=0;i--){var row =_array[i];if (row &&!_newRows.contains(row)){_deletedRows.add(row);}
}
_rows =[];_array =[];_newRows =[];_updatedRows =[];this.raiseCollectionChanged(Web.NotifyCollectionChangedAction.Reset,null);this.raisePropertyChanged("length");if (!oldIsDirty){this.raisePropertyChanged("isDirty");}
}
}
this.getChanges =function(){return {updated :_updatedRows,inserted :_newRows,deleted :_deletedRows};}
this.getColumn =function(name){for (var c =_columns.length -1;c >=0;c--){var column =_columns[c];if (column.get_columnName()==name){return column;}
}
return null;}
this.getItem =function(index){var row =_rows[index];if (!row){var rowObject =_array[index];row =Web.Data.DataRow.isInstanceOfType(rowObject)?rowObject :new Web.Data.DataRow(_array[index],this,index);_rows[index]=row;}
return row;}
this.remove =function(rowObject){if (Web.Data.DataRow.isInstanceOfType(rowObject)){rowObject =rowObject.get__rowObject();}
var oldIsDirty =this.get_isDirty();var index =_array.indexOf(rowObject);var row =this.getItem(index);_array.removeAt(index);_rows.removeAt(index);index =_newRows.indexOf(rowObject);if (index !=-1){_newRows.removeAt(index);}
else {_deletedRows.add(rowObject);}
this.raiseCollectionChanged(Web.NotifyCollectionChangedAction.Remove,row);this.raisePropertyChanged("length");if (oldIsDirty !=this.get_isDirty()){this.raisePropertyChanged("isDirty");}
}
this.dispose =function(){if (this.collectionChanged){this.collectionChanged.dispose();this.collectionChanged =null;}
if (this.propertyChanged){this.propertyChanged.dispose();this.propertyChanged =null;}
var i,row;for (i =_rows.length -1;i >=0;i--){row =_rows[i];if (row){_rows[i].dispose();}
}
for (i =_deletedRows.length -1;i >=0;i--){row =_deletedRows[i];if (row &&row.dispose){row.dispose();}
}
for (i =_newRows.length -1;i >=0;i--){row =_newRows[i];if (row &&row.dispose){row.dispose();}
}
for (i =_updatedRows.length -1;i >=0;i--){row =_updatedRows[i];if (row &&row.dispose){row.dispose();}
}
_rows =null;_deletedRows =null;_newRows =null;_updatedRows =null;_columns =null;_array =null;_keys =null;}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('columns',Array,true);td.addProperty('keys',Array,true);td.addProperty('length',Number,true);td.addProperty('isDirty',Boolean,true);td.addMethod('add');td.addMethod('clear');td.addMethod('remove');td.addEvent('collectionChanged',true);td.addEvent('propertyChanged',true);return td;}
this.initialize =function(){this.collectionChanged.initialize(this);this.propertyChanged.initialize(this);}
this.collectionChanged =new Web.Event(null);this.propertyChanged =new Web.Event(null);this.raiseCollectionChanged =function(action,changedItem){this.collectionChanged.invoke(this,new Web.CollectionChangedEventArgs(action,changedItem));}
this.raiseRowChanged =function(changedItem){if ((_updatedRows.indexOf(changedItem)==-1)&&(_newRows.indexOf(changedItem)==-1)){var oldIsDirty =this.get_isDirty();_updatedRows.add(changedItem);if (!oldIsDirty){this.raisePropertyChanged("isDirty");}
}
}
this.raisePropertyChanged =function(propertyName){this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs(propertyName));}
}
Type.registerSealedClass('Web.Data.DataTable',null,Web.IArray,Web.INotifyPropertyChanged,Web.INotifyCollectionChanged,Web.ITypeDescriptorProvider,Web.IDisposable);Web.Data.DataView =function(){Web.Data.DataView.initializeBase(this);var _data =null;var _filtered =null;var _filters;var _dataChangedDelegate;this.get_data =function(){return _data;}
this.set_data =function(data){_filtered =null;if (_data &&Web.INotifyCollectionChanged.isImplementedBy(_data)){_data.collectionChanged.remove(_dataChangedDelegate);}
_data =data;if (_data){if (!Web.Data.DataTable.isInstanceOfType(_data)){_data =new Web.Data.DataTable(_data);}
_data.collectionChanged.add(_dataChangedDelegate);}
this.raisePropertyChanged('data');this.raisePropertyChanged('filteredData');}
this.get_filteredData =function(){if (!_filtered &&_data){var filtered =[];var filters =this.get_filters();var filterLength =filters.get_length();for (var i =0;i <_data.get_length();i++){var valid =true;var item =_data.getItem(i);for (var j =0;j <filterLength;j++){if (!filters[j].filter(item)){valid =false;break;}
}
if (valid){filtered.add(item);}
}
_filtered =new Web.Data.DataTable(filtered);}
return _filtered;}
this.get_filters =function(){if (!_filters){_filters =Web.Component.createCollection(this);_filters.collectionChanged.add(_dataChangedDelegate);}
return _filters;}
this.get_length =function(){this.get_filteredData();return _filtered ?_filtered.get_length():0;}
this.dispose =function(){if (_filters){_filters.dispose();_filters =null;}
Web.Data.DataView.callBaseMethod(this,'dispose');}
Web.Data.DataView.registerBaseMethod(this,'dispose');this.getDescriptor =function(){var td =Web.Data.DataView.callBaseMethod(this,'getDescriptor');td.addProperty("data",Web.Data.DataTable);td.addProperty("filteredData",Web.Data.DataTable,true);td.addProperty("filters",Array,true);td.addProperty("length",Number,true);return td;}
Web.Data.DataView.registerBaseMethod(this,'getDescriptor');this.initialize =function(){Web.Data.DataView.callBaseMethod(this,'initialize');if (_filters){for (var i =0;i <_filters.length;i++){_filters[i].initialize(this);}
}
}
Web.Data.DataView.registerBaseMethod(this,'initialize');function onDataChanged(sender,args){_filtered =null;this.raisePropertyChanged('filteredData');}
_dataChangedDelegate =Function.createDelegate(this,onDataChanged);this.getItem =function(index){return _filtered ?_filtered[index]:null;}
this._raiseFilterChanged =function(filter){_dataChangedDelegate(this,Web.EventArgs.Empty);}
}
Type.registerClass('Web.Data.DataView',Web.Component);Web.TypeDescriptor.addType('script','dataView',Web.Data.DataView,Web.IArray);Web.Data.DataFilter =function(){Web.Data.DataFilter.initializeBase(this,[false]);this.filter =Function.abstractMethod;this.get_dataContext =function(){var dc =Web.Data.DataFilter.callBaseMethod(this,'get_dataContext');if (!dc){if (this.owner){dc =this.owner.get_dataContext();}
}
return dc;}
Web.Data.DataFilter.registerBaseMethod(this,'get_dataContext');this.dispose =function(){this.owner =null;Web.Data.DataFilter.callBaseMethod(this,'dispose');}
Web.Data.DataFilter.registerBaseMethod(this,'dispose');this.raisePropertyChanged =function(propertyName){Web.Data.DataFilter.callBaseMethod(this,'raisePropertyChanged');if (this.owner){this.owner._raiseFilterChanged(this);}
}
Web.Data.DataFilter.registerBaseMethod(this,'raisePropertyChanged');this.setOwner =function(owner){this.owner =owner;}
}
Type.registerAbstractClass('Web.Data.DataFilter',Web.Component);Web.Data.PropertyFilter =function(){Web.Data.PropertyFilter.initializeBase(this,[false]);var _property;var _value;this.get_property =function(){return _property;}
this.set_property =function(name){_property =name;this.raisePropertyChanged('property');}
this.get_value =function(){return _value;}
this.set_value =function(value){_value =value;this.raisePropertyChanged('value');}
this.filter =function(item){if (Web.ITypeDescriptorProvider.isImplementedBy(item)){return Web.TypeDescriptor.getProperty(item,_property)==_value;}
return item[_property]==_value;}
this.getDescriptor =function(){var td =Web.Data.PropertyFilter.callBaseMethod(this,'getDescriptor');td.addProperty('property',String);td.addProperty('value',String);return td;}
}
Type.registerSealedClass('Web.Data.PropertyFilter',Web.Data.DataFilter);Web.TypeDescriptor.addType('script','propertyFilter',Web.Data.PropertyFilter);Web.Data.DataSource =function(){Web.Data.DataSource.initializeBase(this,[true]);var _data =new Web.Data.DataTable([]);var _serviceURL ="";var _serviceType =Web.Data.ServiceType.DataService;var _selectParameters ={};var _isReady =true;var _dataChangedDelegate;this.get_data =function(){return _data;}
this.set_data =function(data){var oldIsDirtyAndReady =this.get_isDirtyAndReady();var oldIsReady =this.get_isReady();var oldRowCount =this.get_rowCount();if (_data){_data.propertyChanged.remove(_dataChangedDelegate);}
if (data instanceof Array){data =new Web.Data.DataTable(data);}
_data =data;if (_data){_data.propertyChanged.add(_dataChangedDelegate);}
this.raisePropertyChanged('data');if (oldIsDirtyAndReady !=this.get_isDirtyAndReady()){this.raisePropertyChanged('isDirtyAndReady');}
if (oldIsReady !=this.get_isReady()){this.raisePropertyChanged('isReady');}
if (oldRowCount !=this.get_rowCount()){this.raisePropertyChanged('rowCount');}
}
this.get_isDirtyAndReady =function(){return _isReady &&_data &&_data.get_isDirty();}
this.get_isReady =function(){return _isReady;}
this._set_isReady =function(value){if (_isReady !=value){var oldDirtyAndReady =this.get_isDirtyAndReady();_isReady =value;this.raisePropertyChanged("isReady");if (this.get_isDirtyAndReady()!=oldDirtyAndReady){this.raisePropertyChanged("isDirtyAndReady");}
}
}
this.get_selectParameters =function(){return _selectParameters;}
this.get_serviceURL =function(){return _serviceURL;}
this.set_serviceURL =function(url){_serviceURL =url;this.raisePropertyChanged('serviceURL');}
this.get_serviceType =function(){return _serviceURL;}
this.set_serviceType =function(value){_serviceType =value;this.raisePropertyChanged('serviceType');}
this.get_rowCount =function(){if (_data){return _data.get_length();}
return 0;}
this.dispose =function(){if (_data){_data.dispose();}
_data =null;Web.Data.DataSource.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =Web.Data.DataSource.callBaseMethod(this,'getDescriptor');td.addProperty('data',Object);td.addProperty('isDirtyAndReady',Boolean,true);td.addProperty('isReady',Boolean,true);td.addProperty('rowCount',Number,true);td.addProperty('serviceURL',String);td.addProperty('selectParameters',Object,true);td.addProperty('serviceType',Web.Data.ServiceType);td.addMethod('select');td.addMethod('update');td.addEvent('dataAvailable',true);return td;}
this.dataAvailable =this.createEvent();function onDataPropertyChanged(sender,args){switch(args.get_propertyName()){case "isDirty":this.raisePropertyChanged("isDirtyAndReady");break;case "length":this.raisePropertyChanged("rowCount");break;}
}
_dataChangedDelegate =Function.createDelegate(this,onDataPropertyChanged);function onRequestComplete(sender,eventArgs){onSelectComplete.call(this,sender.get_response().get_object());}
function onSelectComplete(rawData){var oldDirtyAndReady =this.get_isDirtyAndReady();this.set_data(rawData);_isReady =true;this.raisePropertyChanged("isReady");if (this.get_isDirtyAndReady()!=oldDirtyAndReady){this.raisePropertyChanged("isDirtyAndReady");}
this.dataAvailable.invoke(this,Web.EventArgs.Empty);}
function ready(){this._set_isReady(true);}
this.select =function(){this._set_isReady(false);if (_serviceType ==Web.Data.ServiceType.DataService){Web.Net.ServiceMethodRequest.callMethod(_serviceURL,"GetData",{parameters:_selectParameters},Function.createDelegate(this,onSelectComplete),Function.createDelegate(this,ready));}
else {var url =Web.Net.WebRequest.createUrl(_serviceURL,_selectParameters);var request =new Web.Net.WebRequest();request.set_url(url);request.completed.add(Function.createDelegate(this,onRequestComplete));request.timeout.add(Function.createDelegate(this,ready));request.invoke();}
}
this.update =function(){if (_data &&_data.get_isDirty()){var changes =_data.getChanges();this._set_isReady(false);if (_serviceType ==Web.Data.ServiceType.DataService){Web.Net.ServiceMethodRequest.callMethod(_serviceURL,"SaveData",{changeList:changes,parameters:_selectParameters},Function.createDelegate(this,onSelectComplete),Function.createDelegate(this,ready));}
else {}
} }
}
Type.registerSealedClass('Web.Data.DataSource',Web.Component);Web.TypeDescriptor.addType('script','dataSource',Web.Data.DataSource);Web.Data.ServiceType =Web.Enum.create('DataService','Handler');Type.registerNamespace('Web.Services');Web.Services.AuthenticationService =new function(){var _path ="ScriptServices/Microsoft/Web/Services/Standard/AuthenticationWebService.asmx";this.login =function(userName,password,onMethodComplete,onMethodTimeout,onMethodError){return Web.Net.ServiceMethodRequest.callMethod(_path,"Login",{userName:userName,password:password},onMethodComplete,onMethodTimeout,onMethodError);}
this.validateUser =function(userName,password,onMethodComplete,onMethodTimeout,onMethodError){return Web.Net.ServiceMethodRequest.callMethod(_path,"ValidateUser",{userName:userName,password:password},onMethodComplete,onMethodTimeout,onMethodError);}
}
Web._Profile =function(){Web._Profile.initializeBase(this);var _properties ={};var _propertyNames;var _isDirty;var _autoSave;Web.Application.registerDisposableObject(this);this.get_autoSave =function(){return _autoSave;}
this.set_autoSave =function(value){_autoSave =value;}
this.get_isDirty =function(){return _isDirty;}
this.get_propertyNames =function(){return _propertyNames;}
this.set_propertyNames =function(value){_propertyNames =value;}
this.loaded =new Web.Event(null);this.propertyChanged =new Web.Event(null);this.saved =new Web.Event(null);this.dispose =function(){this.propertyChanged.dispose();this.loaded.dispose();this.saved.dispose();Web.Application.unregisterDisposableObject(this);}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('autoSave',Boolean);td.addProperty('isDirty',Boolean,true);td.addProperty('propertyNames',Array);td.addMethod('load');td.addMethod('save');td.addEvent('loaded',false);td.addEvent('saved',false);return td;}
this.getProperty =function(name,key){if (_properties){return _properties[name];}
return null;}
this.invokeMethod =function(methodName,parameters){}
this.load =function(){Web.Net.ServiceMethodRequest.callMethod(Web._Profile.WebServicePath,"GetProfile",{properties:_propertyNames },Function.createDelegate(this,this._onRequestComplete),null,null,true);}
this.save =function(){Web.Net.ServiceMethodRequest.callMethod(Web._Profile.WebServicePath,"SetProfile",{values:_properties },Function.createDelegate(this,this._onRequestComplete),null,null,false);}
this._saveIfDirty =function(){if (_isDirty){this.save();}
}
this.setProperty =function(name,value,key){if (!_properties){this._updateProperties({});}
_properties[name]=value;this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs(name));if (!_isDirty){_isDirty =true;this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs('isDirty'));}
if (_autoSave){window.setTimeout(Function.createDelegate(this,this._saveIfDirty),0);}
}
this._onRequestComplete =function(result,response,userContext){if (userContext){this._updateProperties(result);_isDirty =false;this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs(null));this.loaded.invoke(this,Web.EventArgs.Empty);}
else {_isDirty =false;this.propertyChanged.invoke(this,new Web.PropertyChangedEventArgs('isDirty'));this.saved.invoke(this,Web.EventArgs.Empty);}
}
this._updateProperties =function(properties){_properties =properties;this.properties =properties;}
}
Web._Profile.WebServicePath ='ScriptServices/Microsoft/Web/Services/Standard/ProfileWebService.asmx';Type.registerSealedClass('Web._Profile',null,Web.IDisposable,Web.ITypeDescriptorProvider,Web.ICustomTypeDescriptor,Web.INotifyPropertyChanged);Web.TypeDescriptor.addType('script','profile',Web._Profile);Web._Profile.parseFromMarkup =function(type,node,markupContext){if (!markupContext.get_isGlobal()){return null;}
var id;var idAttribute =node.attributes.getNamedItem('id');if (idAttribute){id =idAttribute.nodeValue;node.attributes.removeNamedItem('id')}
Web.TypeDescriptor.initializeInstance(Web.Profile,node,markupContext);if (!Web.Profile.properties){Web.Profile._updateProperties({});Web.Profile.load();}
if (id &&id.length){markupContext.addObject(id,Web.Profile);node.attributes.setNamedItem(idAttribute);}
return Web.Profile;}
Web.Profile =new Web._Profile();window.XMLDOM =function(markup){if (Web.Application.get_type()==Web.ApplicationType.InternetExplorer){var progIDs =['Msxml2.DOMDocument.6.0','Msxml2.DOMDocument.5.0','Msxml2.DOMDocument.4.0','Msxml2.DOMDocument.3.0','Msxml2.DOMDocument'];for (var i =0;i <progIDs.length;i++){try {var xmlDOM =new ActiveXObject(progIDs[i]);xmlDOM.async =false;xmlDOM.loadXML(markup);return xmlDOM;}
catch (ex){}
}
return null;}
else {var domParser =new DOMParser();return domParser.parseFromString(markup,'text/xml');}
}
function _loadIECompatLayer(w){if (!window.XMLHttpRequest){window.XMLHttpRequest =function(){var progIDs =['Msxml2.XMLHTTP','Microsoft.XMLHTTP'];for (var i =0;i <progIDs.length;i++){try {var xmlHttp =new ActiveXObject(progIDs[i]);return xmlHttp;}
catch (ex){}
}
return null;}
}
if (!Debug.breakIntoDebugger){Debug.breakIntoDebugger =function(message){Debug.writeln(message);eval('debugger;');}
}
}
_loadIECompatLayer(window);Type.registerNamespace('Web.UI');function $(elementID){return document.getElementById(elementID);}
Web.UI.visitDOM =function(node,visitorMethod,context,includeRootNode){var childNodes,currentNode,c;var nodeQueue;if (includeRootNode){nodeQueue =[node];}
else {nodeQueue =[];childNodes =node.childNodes;for (c =0;c <childNodes.length;c++){currentNode =childNodes[c];if (currentNode.nodeType ==1){nodeQueue.queue(currentNode);}
}
}
while (nodeQueue.length){currentNode =nodeQueue.dequeue();if (visitorMethod(currentNode,context)){return currentNode;}
childNodes =currentNode.childNodes;for (c =0;c <childNodes.length;c++){currentNode =childNodes[c];if (currentNode.nodeType ==1){nodeQueue.queue(currentNode);}
}
}
return null;}
Web.Attributes.defineAttribute('ValueProperty');Web.UI.VisibilityMode =Web.Enum.create('Hide','Collapse');Web.UI.Control =function(associatedElement){Web.UI.Control.initializeBase(this,[true]);this.element =associatedElement;this.element.control =this;var _oldDisplayMode =this.element.style.displayMode;if (!_oldDisplayMode ||(_oldDisplayMode =='none')){_oldDisplayMode ='';}
var _visibilityMode =Web.UI.VisibilityMode.Hide;var _propertyChangeHandler;var _behaviors;var _parent;this.get_accessKey =function(){return this.element.accessKey;}
this.set_accessKey =function(value){if (this.element.accessKey !=value){this.element.accessKey =value;this.raisePropertyChanged('accessKey');}
}
this.get_associatedElement =function(){if (!_propertyChangeHandler){_propertyChangeHandler =Function.createDelegate(this,this._onPropertyChange);this.element.attachEvent('onpropertychange',_propertyChangeHandler);}
return this.element;}
this.get_behaviors =function(){if (!_behaviors){_behaviors =Web.Component.createCollection(this);}
return _behaviors;}
this.get_cssClass =function(){return this.element.className;}
this.set_cssClass =function(value){if (this.element.className !=value){this.element.className =value;this.raisePropertyChanged('cssClass');}
}
this.get_dataContext =function(){var dc =Web.UI.Control.callBaseMethod(this,'get_dataContext');if (!dc){var parent =this.get_parent();if (parent){dc =parent.get_dataContext();}
}
return dc;}
Web.UI.Control.registerBaseMethod(this,'get_dataContext');this.get_enabled =function(){return !this.element.disabled;}
this.set_enabled =function(value){if (value !=this.get_enabled()){this.element.disabled =!value;this.raisePropertyChanged('enabled');}
}
this.get_parent =function(){if (_parent){return _parent;}
else {var parentElement =this.element.parentNode;while (parentElement){if (parentElement.control){return parentElement.control;}
parentElement =parentElement.parentNode;}
return null;}
}
this.set_parent =function(control){_parent =control;}
this.get_style =function(){if (!_propertyChangeHandler){_propertyChangeHandler =Function.createDelegate(this,this._onPropertyChange);this.element.attachEvent('onpropertychange',_propertyChangeHandler);}
return this.element.style;}
this.get_tabIndex =function(){return this.element.tabIndex;}
this.set_tabIndex =function(value){var old =this.element.tabIndex;this.element.tabIndex =value;if (old !=value){this.raisePropertyChanged('tabIndex');}
}
this.get_visibilityMode =function(){return _visibilityMode;}
this.set_visibilityMode =function(value){if (_visibilityMode !=value){_visibilityMode =value;if (this.get_visible()==false){if (_visibilityMode ==Web.UI.VisibilityMode.Hide){this.element.style.display =_oldDisplayMode;}
else {this.element.style.display ='none';}
}
this.raisePropertyChanged('visibilityMode');}
}
this.get_visible =function(){return (this.element.style.visibility !='hidden');}
this.set_visible =function(value){if (value !=this.get_visible()){this.element.style.visibility =value ?'visible':'hidden';if (value ||(_visibilityMode ==Web.UI.VisibilityMode.Hide)){this.element.style.display =_oldDisplayMode;}
else {this.element.style.display ='none';}
this.raisePropertyChanged('visible');}
}
this.validation =this.createEvent();this.addCssClass =function(className){this.set_cssClass(this.get_cssClass()+' '+className);}
this.containsCssClass =function(className){return Web.UI.Control.containsCssClass(this.element,className);}
this.dispose =function(){if (_propertyChangeHandler){this.element.detachEvent('onpropertychange',_propertyChangeHandler);_propertyChangeHandler =null;}
if (_behaviors){_behaviors.dispose();_behaviors =null;}
if (this.element){this.element.control =null;this.element =null;}
Web.UI.Control.callBaseMethod(this,'dispose');}
Web.UI.Control.registerBaseMethod(this,'dispose');this.findObject =function(id){var object;if (this.element.markupContext){object =this.element.markupContext.findObject(id);}
if (!object){var parent =this.get_parent();if (parent){object =parent.findObject(id);}
else {object =Web.Application.findObject(id);}
}
return object;}
this.focus =function(){this.element.focus();}
this.getDescriptor =function(){var td =Web.UI.Control.callBaseMethod(this,'getDescriptor');td.addProperty('accessKey',String);td.addProperty('associatedElement',Object,true);td.addProperty('behaviors',Array,true);td.addProperty('cssClass',String);td.addProperty('enabled',Boolean);td.addProperty('style',Object,true);td.addProperty('tabIndex',Number);td.addProperty('visible',Boolean);td.addProperty('visibilityMode',Web.UI.VisibilityMode);td.addMethod('addCssClass',[Web.TypeDescriptor.createParameter('className',String)]);td.addMethod('focus');td.addMethod('scrollIntoView');td.addMethod('removeCssClass',[Web.TypeDescriptor.createParameter('className',String)]);td.addMethod('toggleCssClass',[Web.TypeDescriptor.createParameter('className',String)]);return td;}
Web.UI.Control.registerBaseMethod(this,'getDescriptor');this.onBubbleEvent =function(source,args){return false;}
Web.UI.Control.registerBaseMethod(this,'onBubbleEvent');this.raiseBubbleEvent =function(source,args){var currentTarget =this.get_parent();while (currentTarget){if (currentTarget.onBubbleEvent(source,args)){return;}
currentTarget =currentTarget.get_parent();}
}
this.removeCssClass =function(className){Web.UI.Control.removeCssClass(this.element,className);}
this.scrollIntoView =function(){this.element.scrollIntoView();}
this.toggleCssClass =function(className){if (this.containsCssClass(className)){this.removeCssClass(className);}
else {this.addCssClass(className);}
}
this._onPropertyChange =function(){if (window.event.propertyName.startsWith('style')){this.raisePropertyChanged('style');}
else {this.raisePropertyChanged('associatedElement');}
}
}
Type.registerClass('Web.UI.Control',Web.Component);Web.TypeDescriptor.addType('script','control',Web.UI.Control);Web.UI.Control.parseFromMarkup =function(type,node,markupContext){var targetElementID;var targetElementAttribute =node.attributes.getNamedItem('targetElement');if (targetElementAttribute){targetElementID =targetElementAttribute.nodeValue;}
else {var idAttribute =node.attributes.getNamedItem('id');if (idAttribute){targetElementID =idAttribute.nodeValue;}
}
var targetElement;if (targetElementID){targetElement =markupContext.findObject(targetElementID,true);}
if (!targetElement){return null;}
if (targetElementAttribute){node.attributes.removeNamedItem('targetElement');}
var dataContextHidden =false;var dataContext =markupContext.get_dataContext();if (dataContext){dataContextHidden =markupContext.hideDataContext();}
var newControl =new type(targetElement);var control =Web.TypeDescriptor.initializeInstance(newControl,node,markupContext);if (targetElementAttribute){node.attributes.setNamedItem(targetElementAttribute);}
if (control){var id =control.get_id();if (!id){id =targetElementID;}
markupContext.addObject(id,control);if (dataContext){control.set_dataContext(dataContext);}
}
else {newControl.dispose();}
if (dataContextHidden){markupContext.restoreDataContext();}
return control;}
Web.UI.Control.setLocation =function(element,position){element.style.left =position.x +"px";element.style.top =position.y +"px";}
Web.UI.Control.overlaps =function(r1,r2){var xLeft =(r1.x >=r2.x &&r1.x <=(r2.x +r2.width));var xRight =((r1.x +r1.width)>=r2.x &&(r1.x +r1.width)<=r2.x +r2.width);var xComplete =((r1.x <r2.x)&&((r1.x +r1.height)>(r2.x +r2.height)));var yLeft =(r1.y >=r2.y &&r1.y <=(r2.y +r2.height));var yRight =((r1.y +r1.height)>=r2.y &&(r1.y +r1.height)<=r2.y +r2.height);var yComplete =((r1.y <r2.y)&&((r1.y +r1.height)>(r2.y +r2.height)));if ((xLeft ||xRight ||xComplete)&&(yLeft ||yRight ||yComplete)){return true;}
return false;}
Web.UI.Control.getLocation =function(element){var offsetX =0;var offsetY =0;var parent;for (parent =element;parent;parent =parent.offsetParent){if (parent.offsetLeft){offsetX +=parent.offsetLeft;}
if (parent.offsetTop){offsetY +=parent.offsetTop;}
}
return {x:offsetX,y:offsetY };}
Web.UI.Control.getBounds =function(element){var offset =Web.UI.Control.getLocation(element);var width =element.offsetWidth;var height =element.offsetHeight;return {x:offset.x,y:offset.y,width:width,height:height };}
Web.UI.Control.removeCssClass =function(element,className){var currentClassName =' '+element.className +' ';var index =currentClassName.indexOf(' '+className +' ');if (index >=0){var newClassName =(currentClassName.substr(0,index)+' '+currentClassName.substring(index +className.length +1,currentClassName.length)).trim();if (element.control){element.control.set_cssClass(newClassName);}
else {element.className =newClassName;}
}
}
Web.UI.Control.addCssClass =function(element,className){if (element.control){element.control.addCssClass(className);}
else {element.className +=' '+className;}
}
Web.UI.Control.containsCssClass =function(element,className){return element.className.split(' ').contains(className);}
Web.UI.CommandEventArgs =function(commandName,argument){Web.UI.CommandEventArgs.initializeBase(this,[]);var _commandName =commandName;var _argument =argument;this.get_argument =function(){return _argument;}
this.get_commandName =function(){return _commandName;}
this.getDescriptor =function(){var td =Web.UI.CommandEventArgs.callBaseMethod(this,'getDescriptor');td.addProperty('argument',String,true);td.addProperty('commandName',String,true);return td;}
Web.UI.CommandEventArgs.registerBaseMethod(this,'getDescriptor');}
Type.registerClass('Web.UI.CommandEventArgs',Web.EventArgs);Web.UI.Behavior =function(){Web.UI.Behavior.initializeBase(this,[false]);this.get_dataContext =function(){var dc =Web.UI.Behavior.callBaseMethod(this,'get_dataContext');if (!dc){if (this.control){dc =this.control.get_dataContext();}
}
return dc;}
this.dispose =function(){this.control =null;Web.UI.Behavior.callBaseMethod(this,'dispose');}
Web.UI.Behavior.registerBaseMethod(this,'dispose');this.setOwner =function(control){this.control =control;}
}
Type.registerAbstractClass('Web.UI.Behavior',Web.Component);Web.UI.IValidationTarget =function(){this.get_isInvalid =Function.abstractMethod;this.get_validationMessage =Function.abstractMethod;this.validated =null;this.validate =Function.abstractMethod;}
Type.registerInterface('Web.UI.IValidationTarget');Web.UI.Validator =function(){Web.UI.Validator.initializeBase(this);var _errorMessage;var _isInvalid =false;this.get_dataContext =function(){var dc =Web.Component.callBaseMethod(this,'get_dataContext');if (!dc){if (this.control){dc =this.control.get_dataContext();}
}
return dc;}
this.get_errorMessage =function(){return _errorMessage;}
this.set_errorMessage =function(value){_errorMessage =value;}
this.get_isInvalid =function(){return _isInvalid;}
this.getDescriptor =function(){var td =Web.UI.Validator.callBaseMethod(this,'getDescriptor');td.addProperty('errorMessage',String);return td;}
Web.UI.Validator.registerBaseMethod(this,'getDescriptor');this.dispose =function(){this.control =null;Web.UI.Validator.callBaseMethod(this,'dispose');}
Web.UI.Validator.registerBaseMethod(this,'dispose');this.performValidation =function(value){_isInvalid =!this.validate(value);}
this.setOwner =function(control){this.control =control;}
this.validate =Function.abstractMethod;}
Type.registerAbstractClass('Web.UI.Validator',Web.Component);Web.UI.ValidationGroup =function(){Web.UI.ValidationGroup.initializeBase(this);var _associatedControls =[];var _valid =true;var _validated =false;var _validatedHandler;this.get_associatedControls =function(){return _associatedControls;}
this.get_isValid =function(){if (!_validated){this.validate();_validated =true;}
return _valid;}
this.dispose =function(){if (_associatedControls){for (i =0;i <_associatedControls.length;i++){_associatedControls[i].get_component().validated.remove(_validatedHandler);_associatedControls[i].dispose();}
_validatedHandler =null;_associatedControls =null;}
Web.UI.ValidationGroup.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =Web.UI.ValidationGroup.callBaseMethod(this,'getDescriptor');td.addProperty('isValid',Boolean,true);td.addProperty('associatedControls',Array,true);return td;}
this.initialize =function(){Web.UI.ValidationGroup.callBaseMethod(this,'initialize');_validatedHandler =Function.createDelegate(this,this._onControlValidated);for (var i =0;i <_associatedControls.length;i++){_associatedControls[i].get_component().validated.add(_validatedHandler);}
}
this.validate =function(){var valid =true;if (_associatedControls &&_associatedControls.length){for (var i =0;i <_associatedControls.length;i++){if (_associatedControls[i].get_component().get_isInvalid()){valid =false;break;}
}
}
_valid =valid;}
this._onControlValidated =function(sender,eventArgs){var isValid =_valid;this.validate();if (_valid !=isValid){this.raisePropertyChanged('isValid');}
}
}
Type.registerSealedClass('Web.UI.ValidationGroup',Web.Component);Web.TypeDescriptor.addType('script','validationGroup',Web.UI.ValidationGroup);Web.UI.InputControl =function(associatedElement){Web.UI.InputControl.initializeBase(this,[associatedElement]);var _valuePropertyName;var _validators;var _invalid =false;var _validated =false;var _validationMessage;this.get_isInvalid =function(){if (!_validated){this.validate(false);_validated =true;}
return _invalid;}
this.get_validationMessage =function(){return this.get_isInvalid()?_validationMessage :'';}
this.get_validators =function(){if (!_validators){_validators =Web.Component.createCollection(this);}
return _validators;}
this.validated =this.createEvent();this.dispose =function(){if (_validators){_validators.dispose();_validators =null;}
Web.UI.InputControl.callBaseMethod(this,'dispose');}
Web.UI.InputControl.registerBaseMethod(this,'dispose');this.getDescriptor =function(){var td =Web.UI.InputControl.callBaseMethod(this,'getDescriptor');td.addProperty('validators',Array,true);return td;}
Web.UI.InputControl.registerBaseMethod(this,'getDescriptor');this.raisePropertyChanged =function(propertyName){if (_validators &&_validators.length){if (!_valuePropertyName){_valuePropertyName =Web.TypeDescriptor.getAttribute(this,Web.Attributes.ValueProperty);}
if (_valuePropertyName ==propertyName){if (!this.validate(true)){return;}
}
}
Web.UI.InputControl.callBaseMethod(this,'raisePropertyChanged',[propertyName]);}
Web.UI.InputControl.registerBaseMethod(this,'raisePropertyChanged');this.validate =function(raiseEvent){if (!_validators ||!_validators.length){return true;}
if (!_valuePropertyName){_valuePropertyName =Web.TypeDescriptor.getAttribute(this,Web.Attributes.ValueProperty);}
var value =Web.TypeDescriptor.getProperty(this,_valuePropertyName);var invalidValidator =null;for (var i =0;i <_validators.length;i++){var validator =_validators[i];validator.performValidation(value);if (validator.get_isInvalid()){invalidValidator =validator;_validationMessage =invalidValidator.get_errorMessage();_invalid =true;break;}
}
if (!invalidValidator){_invalid =false;}
if (raiseEvent){this.validated.invoke(this,Web.EventArgs.Empty);}
return !_invalid;}
}
Type.registerAbstractClass('Web.UI.InputControl',Web.UI.Control,Web.UI.IValidationTarget);Web.TemplateInstance =function(){this.instanceElement =null;this.callbackResult =null;}
Web.UI.ITemplate =function(){this.createInstance =Function.abstractMethod;this.initialize =Function.abstractMethod;}
Type.registerInterface('Web.UI.ITemplate');Web.TypeDescriptor.addType('script','template',Web.UI.ITemplate);Web.UI.ITemplate.parseFromMarkup =function(type,node,markupContext){var layoutElementID;var layoutElementAttribute =node.attributes.getNamedItem('layoutElement');if (layoutElementAttribute){layoutElementID =layoutElementAttribute.nodeValue;}
else {var idAttribute =node.attributes.getNamedItem('id');if (idAttribute){layoutElementID =idAttribute.nodeValue;}
}
var layoutElement;if (layoutElementID){layoutElement =markupContext.findObject(layoutElementID,true);}
if (!layoutElement){return null;}
return new Web.UI.DeclarativeTemplate(layoutElement,node,markupContext);}
Web.UI.ITemplate.disposeInstance =function(container){if (container.markupContext){container.markupContext.dispose();container.markupContext =null;}
}
Web.UI.DeclarativeTemplate =function(layoutElement,scriptNode,parentMarkupContext){Web.UI.DeclarativeTemplate.initializeBase(this);var _layoutElement =layoutElement;var _scriptNode =scriptNode;var _parentMarkupContext =parentMarkupContext;this.createInstance =function(containerElement,dataContext,instanceElementCreatedCallback,callbackContext){var result =new Web.TemplateInstance();result.instanceElement =_layoutElement.cloneNode(true);var documentContext =document.createDocumentFragment();documentContext.appendChild(result.instanceElement);var markupContext =new Web.TypeDescriptor.MarkupContext(documentContext,false,_parentMarkupContext,dataContext);Web.TypeDescriptor.processMarkupNodes(_scriptNode.childNodes,markupContext);if (instanceElementCreatedCallback){result.callbackResult =instanceElementCreatedCallback(result.instanceElement,markupContext,callbackContext);}
result.instanceElement.markupContext =markupContext;containerElement.appendChild(result.instanceElement);markupContext.complete();return result;}
this.dispose =function(){_layoutElement =null;_scriptNode =null;_parentMarkupContext =null;}
this.initialize =function(){if (_layoutElement.parentNode){_layoutElement.parentNode.removeChild(_layoutElement);}
}
}
Type.registerSealedClass('Web.UI.DeclarativeTemplate',null,Web.UI.ITemplate,Web.IDisposable);Web.UI.DialogResult =Web.Enum.create('OK','Cancel');Web.UI.MessageBoxStyle =Web.Enum.create('OK','OKCancel');Web.UI.Window =new function(){this.messageBox =function(text,style){if (!style){style =Web.UI.MessageBoxStyle.OK;}
var result =Web.UI.DialogResult.OK;switch (style){case Web.UI.MessageBoxStyle.OK:window.alert(text);break;case Web.UI.MessageBoxStyle.OKCancel:if (window.confirm(text)==false){result =Web.UI.DialogResult.Cancel;}
break;}
return result;}
this.inputBox =function(promptText,defaultValue){if (!defaultValue){defaultValue ='';}
return window.prompt(promptText,defaultValue);}
}
Web.UI.Key ={Backspace:8,Tab:9,Return:13,Esc:27,Space:32,PageUp:33,PageDown:34,End:35,Home:36,Left:37,Up:38,Right:39,Down:40,WindowsDelete:46,Delete:127
};Web.UI.Label =function(associatedElement){Web.UI.Label.initializeBase(this,[associatedElement]);this.get_text =function(){return this.element.innerHTML;}
this.set_text =function(value){if (this.element.innerHTML !=value){this.element.innerHTML =value;this.raisePropertyChanged('text');}
}
this.getDescriptor =function(){var td =Web.UI.Label.callBaseMethod(this,'getDescriptor');td.addProperty('text',String);return td;}
Web.UI.Label.registerBaseMethod(this,'getDescriptor');}
Type.registerClass('Web.UI.Label',Web.UI.Control);Web.TypeDescriptor.addType('script','label',Web.UI.Label);Web.UI.Image =function(associatedElement){Web.UI.Image.initializeBase(this,[associatedElement]);this.get_alternateText =function(){return this.element.alt;}
this.set_alternateText =function(value){this.element.alt =value;}
this.get_height =function(){return this.element.height;}
this.set_height =function(value){this.element.height =value;}
this.get_imageURL =function(){return this.element.src;}
this.set_imageURL =function(value){this.element.src =value;}
this.get_width =function(){return this.element.width;}
this.set_width =function(value){this.element.width =value;}
this.getDescriptor =function(){var td =Web.UI.Image.callBaseMethod(this,'getDescriptor');td.addProperty('alternateText',String);td.addProperty('height',Number);td.addProperty('imageURL',String);td.addProperty('width',Number);return td;}
Web.UI.Image.registerBaseMethod(this,'getDescriptor');}
Type.registerClass('Web.UI.Image',Web.UI.Control);Web.TypeDescriptor.addType('script','image',Web.UI.Image);Web.UI.HyperLink =function(associatedElement){Web.UI.HyperLink.initializeBase(this,[associatedElement]);var _clickHandler;this.get_navigateURL =function(){return this.element.href;}
this.set_navigateURL =function(value){this.element.href =value;}
this.getDescriptor =function(){var td =Web.UI.HyperLink.callBaseMethod(this,'getDescriptor');td.addProperty('navigateURL',String);td.addEvent('click',true);return td;}
Web.UI.HyperLink.registerBaseMethod(this,'getDescriptor');this.click =this.createEvent();this.dispose =function(){if (_clickHandler){this.element.detachEvent('onclick',_clickHandler);_clickHandler =null;}
Web.UI.HyperLink.callBaseMethod(this,'dispose');}
this.initialize =function(){Web.UI.HyperLink.callBaseMethod(this,'initialize');_clickHandler =Function.createDelegate(this,this._onClick);this.element.attachEvent('onclick',_clickHandler);}
this._onClick =function(){this.click.invoke(this,Web.EventArgs.Empty);}
}
Type.registerClass('Web.UI.HyperLink',Web.UI.Label);Web.TypeDescriptor.addType('script','hyperLink',Web.UI.HyperLink);Web.UI.Button =function(associatedElement){Web.UI.Button.initializeBase(this,[associatedElement]);var _clickHandler;var _command;var _arg;this.get_argument =function(){return _arg;}
this.set_argument =function(value){if (_arg !=value){_arg =value;this.raisePropertyChanged('argument');}
}
this.get_command =function(){return _command;}
this.set_command =function(value){if (_command !=value){_command =value;this.raisePropertyChanged('command');}
}
this.getDescriptor =function(){var td =Web.UI.Button.callBaseMethod(this,'getDescriptor');td.addProperty('command',String);td.addProperty('argument',String);td.addEvent('click',true);return td;}
Web.UI.Button.registerBaseMethod(this,'getDescriptor');this.click =this.createEvent();this.dispose =function(){if (_clickHandler){this.element.detachEvent('onclick',_clickHandler);_clickHandler =null;}
Web.UI.Button.callBaseMethod(this,'dispose');}
this.initialize =function(){Web.UI.Button.callBaseMethod(this,'initialize');_clickHandler =Function.createDelegate(this,this._onClick);this.element.attachEvent('onclick',_clickHandler);}
this._onClick =function(){this.click.invoke(this,Web.EventArgs.Empty);if (_command){this.raiseBubbleEvent(this,new Web.UI.CommandEventArgs(_command,_arg));}
}
}
Type.registerClass('Web.UI.Button',Web.UI.Control);Web.TypeDescriptor.addType('script','button',Web.UI.Button);Web.UI.CheckBox =function(associatedElement){Web.UI.CheckBox.initializeBase(this,[associatedElement]);var _clickHandler;this.get_checked =function(){return this.element.checked;}
this.set_checked =function(value){if (value !=this.get_checked()){this.element.checked =value;this.raisePropertyChanged('checked');}
}
this.click =this.createEvent();this.getDescriptor =function(){var td =Web.UI.CheckBox.callBaseMethod(this,'getDescriptor');td.addProperty('checked',Boolean);td.addEvent('click',true);return td;}
Web.UI.CheckBox.registerBaseMethod(this,'getDescriptor');this.dispose =function(){if (_clickHandler){this.element.detachEvent('onclick',_clickHandler);_clickHandler =null;}
Web.UI.CheckBox.callBaseMethod(this,'dispose');}
this.initialize =function(){Web.UI.CheckBox.callBaseMethod(this,'initialize');_clickHandler =Function.createDelegate(this,this._onClick);this.element.attachEvent('onclick',_clickHandler);}
this._onClick =function(){this.raisePropertyChanged('checked');this.click.invoke(this,Web.EventArgs.Empty);}
}
Type.registerClass('Web.UI.CheckBox',Web.UI.Control);Web.TypeDescriptor.addType('script','checkBox',Web.UI.CheckBox);Web.UI.Select =function(associatedElement){Web.UI.Select.initializeBase(this,[associatedElement]);var _selectionChangedHandler;var _data;var _dataChangedDelegate;var _textProperty;var _valueProperty;var _firstItemText;this.get_data =function(){return _data;}
this.set_data =function(data){if (_data &&Web.INotifyCollectionChanged.isImplementedBy(_data)){_data.collectionChanged.remove(_dataChangedDelegate);}
_data =data;if (_data){if (!Web.Data.DataTable.isInstanceOfType(_data)){_data =new Web.Data.DataTable(_data);}
_data.collectionChanged.add(_dataChangedDelegate);}
dataBind.call(this);this.raisePropertyChanged('data');}
this.get_firstItemText =function(){return _firstItemText;}
this.set_firstItemText =function(value){if (_firstItemText !=value){_firstItemText =value;this.raisePropertyChanged('firstItemText');dataBind.call(this);}
}
this.get_selectedValue =function(){return this.element.value;}
this.set_selectedValue =function(value){this.element.value =value;}
this.get_textProperty =function(){return _textProperty;}
this.set_textProperty =function(name){_textProperty =name;this.raisePropertyChanged('textProperty');}
this.get_valueProperty =function(){return _valueProperty;}
this.set_valueProperty =function(name){_valueProperty =name;this.raisePropertyChanged('valueProperty');}
this.selectionChanged =this.createEvent();function dataBind(){var options =this.element.options;var selectedValues =[];var i;for (i =options.length -1;i >=0;i--){if (options[i].selected){selectedValues.add(options[i].value);}
options[i]=null;}
var option;if (_firstItemText &&(_firstItemText.length !=0)){option =new Option(_firstItemText,"");options[this.element.length]=option;}
if (_data){var length =_data.get_length();for (i =0;i <length;i++){var item =_data.getItem(i);option =new Option(Web.TypeDescriptor.getProperty(item,_textProperty),Web.TypeDescriptor.getProperty(item,_valueProperty));option.selected =selectedValues.contains(option.value);options[this.element.length]=option;}
}
}
_dataChangedDelegate =Function.createDelegate(this,dataBind);this.dispose =function(){if (_selectionChangedHandler){this.element.detachEvent('onchange',_selectionChangedHandler);_selectionChangedHandler =null;}
Web.UI.Select.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =Web.UI.Select.callBaseMethod(this,'getDescriptor');td.addProperty("data",Web.Data.DataTable);td.addProperty('firstItemText',String);td.addProperty('selectedValue',String);td.addProperty('textProperty',String);td.addProperty('valueProperty',String);td.addEvent('selectionChanged',true);return td;}
Web.UI.Select.registerBaseMethod(this,'getDescriptor');this.initialize =function(){Web.UI.Select.callBaseMethod(this,'initialize');_selectionChangedHandler =Function.createDelegate(this,this._onSelectionChanged);this.element.attachEvent('onchange',_selectionChangedHandler);}
this._onSelectionChanged =function(){this.raisePropertyChanged('selectedValue');this.selectionChanged.invoke(this,Web.EventArgs.Empty);}
}
Type.registerClass('Web.UI.Select',Web.UI.Control);Web.TypeDescriptor.addType('script','select',Web.UI.Select);Web.UI.TextBox =function(associatedElement){Web.UI.TextBox.initializeBase(this,[associatedElement]);var _text;var _changeHandler;var _keyPressHandler;this.get_text =function(){return this.element.value;}
this.set_text =function(value){if (this.element.value !=value){this.element.value =value;this.raisePropertyChanged('text');}
}
this.dispose =function(){if (_changeHandler){this.element.detachEvent('onchange',_changeHandler);_changeHandler =null;}
if (_keyPressHandler){this.element.detachEvent('onkeypress',_keyPressHandler);_keyPressHandler =null;}
Web.UI.TextBox.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =Web.UI.TextBox.callBaseMethod(this,'getDescriptor');td.addProperty('text',String);td.addAttribute(Web.Attributes.ValueProperty,'text');return td;}
Web.UI.TextBox.registerBaseMethod(this,'getDescriptor');this.initialize =function(){Web.UI.TextBox.callBaseMethod(this,'initialize');_text =this.element.value;_changeHandler =Function.createDelegate(this,this._onChanged);this.element.attachEvent('onchange',_changeHandler);_keyPressHandler =Function.createDelegate(this,this._onKeyPress);this.element.attachEvent('onkeypress',_keyPressHandler);}
this._onChanged =function(){if (this.element.value !=_text){_text =this.element.value;this.raisePropertyChanged('text');}
}
this._onKeyPress =function(){var e =window.event;var key =e.keyCode;if (key ==13){if (this.element.value !=_text){_text =this.element.value;this.raisePropertyChanged('text');}
}
}
}
Type.registerClass('Web.UI.TextBox',Web.UI.InputControl);Web.TypeDescriptor.addType('script','textBox',Web.UI.TextBox);Web.UI.PopupBehavior =function(){Web.UI.PopupBehavior.initializeBase(this);var _x =0;var _y =0;var _positioningMode =Web.UI.PositioningMode.Absolute;var _parentElement;var _moveHandler;this.get_parentElement =function(){return _parentElement;}
this.set_parentElement =function(element){_parentElement =element;this.raisePropertyChanged('parentElement');}
this.get_positioningMode =function(){return _positioningMode;}
this.set_positioningMode =function(mode){_positioningMode =mode;this.raisePropertyChanged('positioningMode');}
this.get_x =function(){return _x;}
this.set_x =function(x){_x =x;if (this.control.get_visible()){this.show();}
this.raisePropertyChanged('x');}
this.get_y =function(){return _y;}
this.set_y =function(y){_y =y;if (this.control.get_visible()){this.show();}
this.raisePropertyChanged('y');}
this.hide =function(){this.control.set_visible(false);var elt =this.control.element;if (elt.originalWidth){elt.style.width =elt.originalWidth +"px";elt.originalWidth =null;}
if (window.navigator &&window.navigator.appName =="Microsoft Internet Explorer"&&!window.opera){var childFrame =elt._hideWindowedElementsIFrame;if (childFrame){childFrame.style.display ="none";}
}
}
this.show =function(){this.control.set_visible(true);var elt =this.control.element;var offsetParent =elt.offsetParent;if (!offsetParent)offsetParent =document.documentElement;var offsetParentLocation =Web.UI.Control.getLocation(offsetParent);var parent =_parentElement ?_parentElement :offsetParent;var parentBounds =Web.UI.Control.getBounds(parent);var diff ={x:parentBounds.x -offsetParentLocation.x,y:parentBounds.y -offsetParentLocation.y};var width =elt.offsetWidth -(elt.clientLeft ?elt.clientLeft *2 :0);var height =elt.offsetHeight -(elt.clientTop ?elt.clientTop *2 :0);var position;switch (_positioningMode){case Web.UI.PositioningMode.Center:position ={x:Math.round(parentBounds.width /2 -width /2),y:Math.round(parentBounds.height /2 -height /2)};break;case Web.UI.PositioningMode.BottomLeft:position ={x:0,y:parentBounds.height
};break;case Web.UI.PositioningMode.BottomRight:position ={x:parentBounds.width -width,y:parentBounds.height
};break;case Web.UI.PositioningMode.TopLeft:position ={x:0,y:-elt.offsetHeight
};break;case Web.UI.PositioningMode.TopRight:position ={x:parentBounds.width -width,y:-elt.offsetHeight
};break;default:position ={x:0,y:0};}
position.x +=_x +diff.x;position.y +=_y +diff.y;Web.UI.Control.setLocation(elt,position);elt.style.width =width +"px";var newPosition =Web.UI.Control.getBounds(elt);var documentWidth =self.innerWidth ?self.innerWidth :document.documentElement.clientWidth;if (!documentWidth){documentWidth =document.body.clientWidth;}
if (newPosition.x +newPosition.width >documentWidth -5){position.x -=newPosition.x +newPosition.width -documentWidth +5;}
if (newPosition.x <0){position.x -=newPosition.x;}
if (newPosition.y <0){position.y -=newPosition.y;}
Web.UI.Control.setLocation(elt,position);if ((Web.Application.get_type()==Web.ApplicationType.InternetExplorer)&&!window.opera){var childFrame =elt._hideWindowedElementsIFrame;if (!childFrame){childFrame =document.createElement("iframe");childFrame.src ="about:blank";childFrame.style.position ="absolute";childFrame.style.display ="none";childFrame.scrolling ="no";childFrame.frameBorder ="0";childFrame.style.filter ="progid:DXImageTransform.Microsoft.Alpha(style=0,opacity=0)";elt.parentNode.insertBefore(childFrame,elt);elt._hideWindowedElementsIFrame =childFrame;_moveHandler =Function.createDelegate(this,moveHandler);elt.attachEvent('onmove',_moveHandler);}
childFrame.style.top =elt.style.top;childFrame.style.left =elt.style.left;childFrame.style.width =elt.offsetWidth +"px";childFrame.style.height =elt.offsetHeight +"px";childFrame.style.display =elt.style.display;if (elt.currentStyle &&elt.currentStyle.zIndex){childFrame.style.zIndex =elt.currentStyle.zIndex;}
else if (elt.style.zIndex){childFrame.style.zIndex =elt.style.zIndex;}
}
}
this.getDescriptor =function(){var td =Web.UI.PopupBehavior.callBaseMethod(this,'getDescriptor');td.addProperty('parentElement',Object,false,Web.Attributes.Element,true);td.addProperty('positioningMode',Web.UI.PositioningMode);td.addProperty('x',Number);td.addProperty('y',Number);td.addMethod('show');td.addMethod('hide');return td;}
Web.UI.PopupBehavior.registerBaseMethod(this,'getDescriptor');this.initialize =function(){Web.UI.PopupBehavior.callBaseMethod(this,'initialize');this.hide();this.control.element.style.position ="absolute";}
Web.UI.PopupBehavior.registerBaseMethod(this,'initialize');this.dispose =function(){if (_moveHandler &&this.control &&this.control.element){this.control.element.detachEvent('onmove',_moveHandler);}
_parentElement =null;Web.UI.PopupBehavior.callBaseMethod(this,'dispose');}
Web.UI.PopupBehavior.registerBaseMethod(this,'dispose');function moveHandler(){var elt =this.control.element;if (elt._hideWindowedElementsIFrame){elt.parentNode.insertBefore(elt._hideWindowedElementsIFrame,elt);elt._hideWindowedElementsIFrame.style.top =elt.style.top;elt._hideWindowedElementsIFrame.style.left =elt.style.left;}
}
}
Type.registerClass('Web.UI.PopupBehavior',Web.UI.Behavior);Web.TypeDescriptor.addType('script','popupBehavior',Web.UI.PopupBehavior);Web.UI.PositioningMode =Web.Enum.create('Absolute','Center','BottomLeft','BottomRight','TopLeft','TopRight');Web.UI.ClickBehavior =function(){Web.UI.ClickBehavior.initializeBase(this);var _clickHandler;this.click =this.createEvent();this.dispose =function(){this.control.element.detachEvent('onclick',_clickHandler);Web.UI.ClickBehavior.callBaseMethod(this,'dispose');}
this.initialize =function(){Web.UI.ClickBehavior.callBaseMethod(this,'initialize');_clickHandler =Function.createDelegate(this,clickHandler);this.control.element.attachEvent('onclick',_clickHandler);}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addEvent('click',true);return td;}
function clickHandler(){this.click.invoke(this,Web.EventArgs.Empty);}
}
Type.registerSealedClass('Web.UI.ClickBehavior',Web.UI.Behavior);Web.TypeDescriptor.addType('script','clickBehavior',Web.UI.ClickBehavior);Web.UI.HoverBehavior =function(){Web.UI.HoverBehavior.initializeBase(this);var _hoverHandler;var _unHoverHandler;var _hoverElement;var _unhoverDelay =0;var _hoverCount =0;this.get_hoverElement =function(){return _hoverElement;}
this.set_hoverElement =function(element){_hoverElement =element;this.raisePropertyChanged('hoverElement');}
this.get_unhoverDelay =function(){return _unhoverDelay;}
this.set_unhoverDelay =function(ms){_unhoverDelay =ms;this.raisePropertyChanged('unhoverDelay');}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('hoverElement',Object,false,Web.Attributes.Element,true);td.addProperty('unhoverDelay',Number);td.addEvent('hover',true);td.addEvent('unhover',true);return td;}
this.hover =this.createEvent();this.unhover =this.createEvent();this.dispose =function(){if (_hoverHandler){this.control.element.detachEvent('onmouseover',_hoverHandler);this.control.element.detachEvent('onfocus',_hoverHandler);_hoverHandler =null;}
if (_unHoverHandler){this.control.element.detachEvent('onmouseout',_unHoverHandler);this.control.element.detachEvent('onblur',_unHoverHandler);_hoverHandler =null;}
Web.UI.HoverBehavior.callBaseMethod(this,'dispose');}
this.initialize =function(){Web.UI.HoverBehavior.callBaseMethod(this,'initialize');_hoverHandler =Function.createDelegate(this,hoverHandler);this.control.element.attachEvent('onmouseover',_hoverHandler);this.control.element.attachEvent('onfocus',_hoverHandler);_unHoverHandler =Function.createDelegate(this,_unhoverDelay ?delayedUnhoverHandler :unHoverHandler);this.control.element.attachEvent('onmouseout',_unHoverHandler);this.control.element.attachEvent('onblur',_unHoverHandler);if (_hoverElement){_hoverElement.attachEvent('onmouseover',_hoverHandler);_hoverElement.attachEvent('onfocus',_hoverHandler);_hoverElement.attachEvent('onmouseout',_unHoverHandler);_hoverElement.attachEvent('onblur',_unHoverHandler);}
}
function delayedUnhoverHandler(){window.setTimeout(Function.createDelegate(this,unHoverHandler),_unhoverDelay);}
function hoverHandler(){_hoverCount++;this.hover.invoke(this,Web.EventArgs.Empty);}
function unHoverHandler(){_hoverCount--;if (_hoverCount ==0){this.unhover.invoke(this,Web.EventArgs.Empty);}
}
}
Type.registerSealedClass('Web.UI.HoverBehavior',Web.UI.Behavior);Web.TypeDescriptor.addType('script','hoverBehavior',Web.UI.HoverBehavior);Web.UI.AutoCompleteBehavior =function(){Web.UI.AutoCompleteBehavior.initializeBase(this);var _serviceURL;var _serviceMethod;var _minimumPrefixLength =3;var _completionSetCount =10;var _completionInterval =1000;var _completionListElement;var _popupBehavior;var _timer;var _cache;var _currentPrefix;var _selectIndex;var _focusHandler;var _blurHandler;var _keyDownHandler;var _mouseDownHandler;var _mouseUpHandler;var _mouseOverHandler;var _tickHandler;this.get_completionInterval =function(){return _completionInterval;}
this.set_completionInterval =function(value){_completionInterval =value;}
this.get_completionList =function(){return _completionListElement;}
this.set_completionList =function(value){_completionListElement =value;}
this.get_completionSetCount =function(){return _completionSetCount;}
this.set_completionSetCount =function(value){_completionSetCount =value;}
this.get_minimumPrefixLength =function(){return _minimumPrefixLength;}
this.set_minimumPrefixLength =function(value){_minimumPrefixLength =value;}
this.get_serviceMethod =function(){return _serviceMethod;}
this.set_serviceMethod =function(value){_serviceMethod =value;}
this.get_serviceURL =function(){return _serviceURL;}
this.set_serviceURL =function(value){_serviceURL =value;}
this.dispose =function(){if (_timer){_timer.tick.remove(_tickHandler);_timer.dispose();}
var element =this.control.element;element.detachEvent('onfocus',_focusHandler);element.detachEvent('onblur',_blurHandler);element.detachEvent('onkeydown',_keyDownHandler);_completionListElement.detachEvent('onmousedown',_mouseDownHandler);_completionListElement.detachEvent('onmouseup',_mouseUpHandler);_completionListElement.detachEvent('onmouseover',_mouseOverHandler);_tickHandler =null;_focusHandler =null;_blurHandler =null;_keyDownHandler =null;_mouseDownHandler =null;_mouseUpHandler =null;_mouseOverHandler =null;Web.UI.AutoCompleteBehavior.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =new Web.TypeDescriptor();td.addProperty('completionInterval',Number);td.addProperty('completionList',Object,false,Web.Attributes.Element,true);td.addProperty('completionSetCount',Number);td.addProperty('minimumPrefixLength',Number);td.addProperty('serviceMethod',String);td.addProperty('serviceURL',String);return td;}
this.initialize =function(){Web.UI.AutoCompleteBehavior.callBaseMethod(this,'initialize');_tickHandler =Function.createDelegate(this,this._onTimerTick);_focusHandler =Function.createDelegate(this,this._onGotFocus);_blurHandler =Function.createDelegate(this,this._onLostFocus);_keyDownHandler =Function.createDelegate(this,this._onKeyDown);_mouseDownHandler =Function.createDelegate(this,this._onListMouseDown);_mouseUpHandler =Function.createDelegate(this,this._onListMouseUp);_mouseOverHandler =Function.createDelegate(this,this._onListMouseOver);_timer =new Web.Timer();_timer.set_interval(_completionInterval);_timer.tick.add(_tickHandler);var element =this.control.element;element.autocomplete ="off";element.attachEvent('onfocus',_focusHandler);element.attachEvent('onblur',_blurHandler);element.attachEvent('onkeydown',_keyDownHandler);var elementBounds =Web.UI.Control.getBounds(element);if (!_completionListElement){_completionListElement =document.createElement('DIV');document.body.appendChild(_completionListElement);}
var completionListStyle =_completionListElement.style;completionListStyle.visibility ='hidden';completionListStyle.backgroundColor ='window';completionListStyle.color ='windowtext';completionListStyle.border ='solid 1px buttonshadow';completionListStyle.cursor ='default';completionListStyle.unselectable ='unselectable';completionListStyle.overflow ='hidden';completionListStyle.width =(elementBounds.width -2)+'px';_completionListElement.attachEvent('onmousedown',_mouseDownHandler);_completionListElement.attachEvent('onmouseup',_mouseUpHandler);_completionListElement.attachEvent('onmouseover',_mouseOverHandler);document.body.appendChild(_completionListElement);var popupControl =new Web.UI.Control(_completionListElement);_popupBehavior =new Web.UI.PopupBehavior();_popupBehavior.set_parentElement(element);_popupBehavior.set_positioningMode(Web.UI.PositioningMode.BottomLeft);popupControl.get_behaviors().add(_popupBehavior);_popupBehavior.initialize();popupControl.initialize();}
this._hideCompletionList =function(){_popupBehavior.hide();_completionListElement.innerHTML ='';_selectIndex =-1;}
this._highlightItem =function(item){var children =_completionListElement.childNodes;for (var i =0;i <children.length;i++){var child =children[i];if (child !=item){child.style.backgroundColor ='window';child.style.color ='windowtext';}
}
item.style.backgroundColor ='highlight';item.style.color ='highlighttext';}
this._onListMouseDown =function(){this._setText(window.event.srcElement.innerHTML);}
this._onListMouseUp =function(){this.control.focus();}
this._onListMouseOver =function(){var item =window.event.srcElement;_selectIndex =-1;this._highlightItem(item);}
this._onGotFocus =function(){_timer.set_enabled(true);}
this._onKeyDown =function(){var e =window.event;if (e.keyCode ==27){this._hideCompletionList();e.returnValue =false;}
else if (e.keyCode ==Web.UI.Key.Up){if (_selectIndex >0){_selectIndex--;this._highlightItem(_completionListElement.childNodes[_selectIndex]);e.returnValue =false;}
}
else if (e.keyCode ==Web.UI.Key.Down){if (_selectIndex <(_completionListElement.childNodes.length -1)){_selectIndex++;this._highlightItem(_completionListElement.childNodes[_selectIndex]);e.returnValue =false;}
}
else if (e.keyCode ==Web.UI.Key.Return){if (_selectIndex !=-1){this._setText(_completionListElement.childNodes[_selectIndex].innerHTML);e.returnValue =false;}
}
if (e.keyCode !=Web.UI.Key.Tab){_timer.set_enabled(true);}
}
this._onLostFocus =function(){_timer.set_enabled(false);this._hideCompletionList();}
function _onMethodComplete(result,response,context){var acBehavior =context[0];var prefixText =context[1];acBehavior._update(prefixText,result,true);}
this._onTimerTick =function(sender,eventArgs){if (_serviceURL &&_serviceMethod){var text =this.control.element.value;if (text.trim().length <_minimumPrefixLength){this._update('',null,false);return;}
if (_currentPrefix !=text){_currentPrefix =text;if (_cache &&_cache[text]){this._update(text,_cache[text],false);return;}
Web.Net.ServiceMethodRequest.callMethod(_serviceURL,_serviceMethod,{prefixText :_currentPrefix,count:_completionSetCount },_onMethodComplete,null,null,[this,text ]);}
}
}
this._setText =function(text){_timer.set_enabled(false);_currentPrefix =text;this.control.element.value =text;this._hideCompletionList();}
this._update =function(prefixText,completionItems,cacheResults){if (cacheResults){if (!_cache){_cache ={};}
_cache[prefixText]=completionItems;}
_completionListElement.innerHTML ='';_selectIndex =-1;if (completionItems &&completionItems.length){for (var i =0;i <completionItems.length;i++){var itemElement =document.createElement('div');itemElement.innerHTML =completionItems[i];itemElement.__item ='';var itemElementStyle =itemElement.style;itemElementStyle.padding ='1px';itemElementStyle.textAlign ='left';itemElementStyle.textOverflow ='ellipsis';itemElementStyle.backgroundColor ='window';itemElementStyle.color ='windowtext';_completionListElement.appendChild(itemElement);}
_popupBehavior.show();}
else {_popupBehavior.hide();}
}
}
Type.registerSealedClass('Web.UI.AutoCompleteBehavior',Web.UI.Behavior);Web.TypeDescriptor.addType('script','autoComplete',Web.UI.AutoCompleteBehavior);Web.UI.RequiredFieldValidator =function(){Web.UI.RequiredFieldValidator.initializeBase(this);this.validate =function(value){if (!value){return false;}
if (String.isInstanceOfType(value)){if (value.length ==0){return false;}
}
return true;}
}
Type.registerSealedClass('Web.UI.RequiredFieldValidator',Web.UI.Validator);Web.TypeDescriptor.addType('script','requiredFieldValidator',Web.UI.RequiredFieldValidator);Web.UI.TypeValidator =function(){Web.UI.TypeValidator.initializeBase(this);var _type;this.get_type =function(){return _type;}
this.set_type =function(value){_type =value;}
this.getDescriptor =function(){var td =Web.UI.TypeValidator.callBaseMethod(this,'getDescriptor');td.addProperty('type',Function);return td;}
this.validate =function(value){var valid =true;if (value &&value.length){try {var number =_type.parse(value);if (isNaN(number)){valid =false;}
}
catch (ex){valid =false;}
}
return valid;}
}
Type.registerSealedClass('Web.UI.TypeValidator',Web.UI.Validator);Web.TypeDescriptor.addType('script','typeValidator',Web.UI.TypeValidator);Web.UI.RangeValidator =function(){Web.UI.RangeValidator.initializeBase(this);var _lowerBound;var _upperBound;this.get_lowerBound =function(){return _lowerBound;}
this.set_lowerBound =function(value){_lowerBound =value;}
this.get_upperBound =function(){return _upperBound;}
this.set_upperBound =function(value){_upperBound =value;}
this.getDescriptor =function(){var td =Web.UI.RangeValidator.callBaseMethod(this,'getDescriptor');td.addProperty('lowerBound',Number);td.addProperty('upperBound',Number);return td;}
this.validate =function(value){if (value &&value.length){return ((value <=_upperBound)&&(value >=_lowerBound));}
return true;}
}
Type.registerSealedClass('Web.UI.RangeValidator',Web.UI.Validator);Web.TypeDescriptor.addType('script','rangeValidator',Web.UI.RangeValidator);Web.UI.RegexValidator =function(){Web.UI.RegexValidator.initializeBase(this);var _regex;this.get_regex =function(){return _regex;}
this.set_regex =function(value){_regex =value;}
this.getDescriptor =function(){var td =Web.UI.RegexValidator.callBaseMethod(this,'getDescriptor');td.addProperty('regex',RegExp);return td;}
this.validate =function(value){if (value &&value.length){var matches =_regex.exec(value);return (matches &&(matches[0]==value));}
return true;}
}
Type.registerSealedClass('Web.UI.RegexValidator',Web.UI.Validator);Web.TypeDescriptor.addType('script','regexValidator',Web.UI.RegexValidator);Web.UI.CustomValidationEventArgs =function(value){Web.UI.CustomValidationEventArgs.initializeBase(this);var _value =value;var _isValid =true;this.get_value =function(){return _value;}
this.get_isValid =function(){return _isValid;}
this.set_isValid =function(value){_isValid =value;}
}
Web.UI.CustomValidator =function(){Web.UI.CustomValidator.initializeBase(this);this.validateValue =this.createEvent();this.getDescriptor =function(){var td =Web.UI.CustomValidator.callBaseMethod(this,'getDescriptor');td.addEvent('validateValue',false);return td;}
this.validate =function(value){if (value &&value.length){var cve =new Web.UI.CustomValidationEventArgs(value);this.validateValue.invoke(this,cve);return cve.get_isValid();}
return true;}
}
Type.registerSealedClass('Web.UI.CustomValidator',Web.UI.Validator);Web.TypeDescriptor.addType('script','customValidator',Web.UI.CustomValidator);Web.UI.ValidationErrorLabel =function(associatedElement){Web.UI.ValidationErrorLabel.initializeBase(this,[associatedElement]);var _associatedControl;var _validatedHandler;this.get_associatedControl =function(){return _associatedControl;}
this.set_associatedControl =function(value){if (_associatedControl &&_validatedHandler){_associatedControl.validated.remove(_validatedHandler);}
if (Web.UI.IValidationTarget.isImplementedBy(value)){_associatedControl =value;}
if (_associatedControl){if (!_validatedHandler){_validatedHandler =Function.createDelegate(this,this._onControlValidated);}
_associatedControl.validated.add(_validatedHandler);}
}
this.dispose =function(){if (_associatedControl){if (_validatedHandler){_associatedControl.validated.remove(_validatedHandler);_validatedHandler =null;}
_associatedControl =null;}
Web.UI.ValidationErrorLabel.callBaseMethod(this,'dispose');}
this.getDescriptor =function(){var td =Web.UI.ValidationErrorLabel.callBaseMethod(this,'getDescriptor');td.addProperty('associatedControl',Object);return td;}
this.initialize =function(){Web.UI.ValidationErrorLabel.callBaseMethod(this,'initialize');this.set_visible(false);}
this._onControlValidated =function(sender,eventArgs){var isInvalid =_associatedControl.get_isInvalid();var tooltip ='';if (isInvalid){tooltip =_associatedControl.get_validationMessage();}
this.set_visible(isInvalid);this.element.title =tooltip;}
}
Type.registerSealedClass('Web.UI.ValidationErrorLabel',Web.UI.Label);Web.TypeDescriptor.addType('script','validationErrorLabel',Web.UI.ValidationErrorLabel);Type.registerNamespace('Web.UI.Data');Web.UI.Data.DataControl =function(associatedElement){Web.UI.Data.DataControl.initializeBase(this,[associatedElement]);var _data;var _dataIndex =0;var _dataChangedDelegate;this._renderPending =true;function prepareChange(){return {dataIndex:this.get_dataIndex(),canMoveNext:this.get_canMoveNext(),canMovePrevious:this.get_canMovePrevious()};}
function triggerChangeEvents(oldState){var dataIndex =this.get_dataIndex();if (oldState.dataIndex !=dataIndex){this.raisePropertyChanged('dataIndex');oldState.dataIndex =dataIndex;}
var canMoveNext =this.get_canMoveNext();if (oldState.canMoveNext !=canMoveNext){this.raisePropertyChanged('canMoveNext');oldState.canMoveNext =canMoveNext;}
var canMovePrevious =this.get_canMovePrevious();if (oldState.canMovePrevious !=canMovePrevious){this.raisePropertyChanged('canMovePrevious');oldState.canMovePrevious =canMovePrevious;}
}
this.get_canMoveNext =function(){if (!_data)return false;return (_dataIndex <_data.get_length()-1);}
this.get_canMovePrevious =function(){if (!_data)return false;return (_dataIndex >0);}
this.get_data =function(){return _data;}
this.set_data =function(value){var oldState =prepareChange.call(this);if (_data &&Web.INotifyCollectionChanged.isImplementedBy(_data)){_data.collectionChanged.remove(_dataChangedDelegate);}
_data =value;if (_data){if (!Web.Data.DataTable.isInstanceOfType(_data)){_data =new Web.Data.DataTable(_data);}
_data.collectionChanged.add(_dataChangedDelegate);}
var newLength =_data ?_data.get_length():0;if (_dataIndex >=newLength){this.set_dataIndex(0);}
if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('data');triggerChangeEvents.call(this,oldState);}
this.get_dataContext =function(){return this.get_dataItem();}
Web.UI.Data.DataControl.registerBaseMethod(this,'get_dataContext');this.get_dataIndex =function(){return _dataIndex;}
this.set_dataIndex =function(value){if (_dataIndex !=value){var oldState =prepareChange.call(this);_dataIndex =value;triggerChangeEvents.call(this,oldState);}
}
Web.UI.Data.DataControl.registerBaseMethod(this,'set_dataIndex');this.get_dataItem =function(){if (_data){return _data.getItem(_dataIndex);}
return null;}
this.get_length =function(){return Web.IArray.isImplementedBy(_data)?_data.get_length():0;}
this.getDescriptor =function(){var td =Web.UI.Data.DataControl.callBaseMethod(this,'getDescriptor');td.addProperty('canMoveNext',Boolean,true);td.addProperty('canMovePrevious',Boolean,true);td.addProperty('data',Web.Data.DataTable);td.addProperty('dataIndex',Number);td.addProperty('dataItem',Object,true);td.addProperty("length",Number,true);td.addMethod('addItem');td.addMethod('deleteCurrentItem');td.addMethod('moveNext');td.addMethod('movePrevious');return td;}
Web.UI.Data.DataControl.registerBaseMethod(this,'getDescriptor');this.addItem =function(){if (_data){var oldState =prepareChange.call(this);_data.add({});this.set_dataIndex(_data.get_length()-1);triggerChangeEvents.call(this,oldState);}
}
this.deleteCurrentItem =function(){if (_data){var oldState =prepareChange.call(this);_data.remove(this.get_dataItem());if (this.get_dataIndex()>=_data.get_length()){this.set_dataIndex(_data.get_length()-1);}
triggerChangeEvents.call(this,oldState);}
}
this.getItem =function(index){if (_data){return _data.getItem(_dataIndex);}
return null;}
this.moveNext =function(){if (_data){var oldState =prepareChange.call(this);var newIndex =this.get_dataIndex()+1;if (newIndex <_data.get_length()){this.set_dataIndex(newIndex);}
triggerChangeEvents.call(this,oldState);}
}
this.movePrevious =function(){if (_data){var oldState =prepareChange.call(this);var newIndex =this.get_dataIndex()-1;if (newIndex >=0){this.set_dataIndex(newIndex);}
triggerChangeEvents.call(this,oldState);}
}
this.onBubbleEvent =function(source,args){if (args.get_commandName()=="select"){var arg =args.get_argument();if (!arg &&arg !=0){var dataContext =source.get_dataContext();if (dataContext){arg =dataContext.get__index();}
}
if (arg &&String.isInstanceOfType(arg)){arg =Number.parse(arg);}
if (arg ||arg ==0){this.set_dataIndex(arg);return true;}
}
return false;}
Web.UI.Control.registerBaseMethod(this,'onBubbleEvent');function onDataChanged(sender,args){this.render();}
_dataChangedDelegate =Function.createDelegate(this,onDataChanged);}
Type.registerClass('Web.UI.Data.DataControl',Web.UI.Control,Web.IArray);Web.UI.Data.ItemView =function(associatedElement){Web.UI.Data.ItemView.initializeBase(this,[associatedElement]);var _itemTemplate;var _emptyTemplate;var _keyDownHandler;this.set_dataIndex =function(value){if (this.get_dataIndex()!=value){Web.UI.Data.ItemView.callBaseMethod(this,'set_dataIndex',[value]);if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
}
}
this.get_emptyTemplate =function(){return _emptyTemplate;}
this.set_emptyTemplate =function(value){if (_emptyTemplate){_emptyTemplate.dispose();}
_emptyTemplate =value;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('emptyTemplate');}
this.get_itemTemplate =function(){return _itemTemplate;}
this.set_itemTemplate =function(value){if (_itemTemplate){_itemTemplate.dispose();}
_itemTemplate =value;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('itemTemplate');}
this.dispose =function(){if (this.element){this.element.detachEvent('onkeydown',_keyDownHandler);}
if (_itemTemplate){_itemTemplate.dispose();_itemTemplate =null;}
if (_emptyTemplate){_emptyTemplate.dispose();_emptyTemplate =null;}
Web.UI.Data.ItemView.callBaseMethod(this,'dispose');}
Web.UI.Data.ItemView.registerBaseMethod(this,'dispose');this.getDescriptor =function(){var td =Web.UI.Data.ItemView.callBaseMethod(this,'getDescriptor');td.addProperty('itemTemplate',Web.UI.ITemplate);td.addProperty('emptyTemplate',Web.UI.ITemplate);return td;}
Web.UI.Data.ItemView.registerBaseMethod(this,'getDescriptor');this.initialize =function(){_keyDownHandler =Function.createDelegate(this,this._onKeyDown);Web.UI.Data.ItemView.callBaseMethod(this,'initialize');this.element.attachEvent('onkeydown',_keyDownHandler);if (_itemTemplate){_itemTemplate.initialize();}
if (_emptyTemplate){_emptyTemplate.initialize();}
this.render();}
this._onKeyDown =function(){var e =window.event;if (e.srcElement ==this.element){if ((e.keyCode ==Web.UI.Key.Up)||(e.keyCode ==Web.UI.Key.Left)){this.movePrevious();e.returnValue =false;}
else if ((e.keyCode ==Web.UI.Key.Down)||(e.keyCode ==Web.UI.Key.Right)){this.moveNext();e.returnValue =false;}
}
}
this.render =function(){if (this.element.childNodes.length){Web.UI.ITemplate.disposeInstance(this.element);}
this.element.innerHTML ='';var template;var data =this.get_data();if (data &&data.get_length()){template =_itemTemplate;}
else {template =_emptyTemplate;}
if (template){template.createInstance(this.element,this.get_dataContext());}
this._renderPending =false;}
}
Type.registerClass('Web.UI.Data.ItemView',Web.UI.Data.DataControl);Web.TypeDescriptor.addType('script','itemView',Web.UI.Data.ItemView);Web.UI.Data.ListView =function(associatedElement){Web.UI.Data.ListView.initializeBase(this,[associatedElement]);var _itemClass;var _alternatingItemClass;var _separatorClass;var _selectedItemClass;var _focusHandler;var _keyDownHandler;var _itemFocusHandler;var _itemClickHandler;var _focusIndex;var _layoutTemplate =null;var _itemTemplate =null;var _separatorTemplate =null;var _emptyTemplate =null;var _itemTemplateParentElementId;var _itemElements =[];var _separatorElements =[];this.get_alternatingItemCssClass =function(){return _alternatingItemClass;}
this.set_alternatingItemCssClass =function(value){if (value !=_alternatingItemClass){_alternatingItemClass =value;this.render();this.raisePropertyChanged('alternatingItemCssClass');}
}
this.set_dataIndex =function(value){var oldIndex =this.get_dataIndex();if (oldIndex !=value){var sel =this.getItemElement(oldIndex);if (sel &&_selectedItemClass){Web.UI.Control.removeCssClass(sel,_selectedItemClass);}
Web.UI.Data.ListView.callBaseMethod(this,'set_dataIndex',[value]);sel =this.getItemElement(value);if (sel &&_selectedItemClass){Web.UI.Control.addCssClass(sel,_selectedItemClass);}
}
}
this.get_emptyTemplate =function(){return _emptyTemplate;}
this.set_emptyTemplate =function(template){if (_emptyTemplate){_emptyTemplate.dispose();}
_emptyTemplate =template;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('emptyTemplate');}
this.get_itemCssClass =function(){return _itemClass;}
this.set_itemCssClass =function(value){if (value !=_itemClass){_itemClass =value;this.render();this.raisePropertyChanged('itemCssClass');}
}
this.get_itemTemplate =function(){return _itemTemplate;}
this.set_itemTemplate =function(template){if (_itemTemplate){_itemTemplate.dispose();}
_itemTemplate =template;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('itemTemplate');}
this.get_itemTemplateParentElementId =function(){return _itemTemplateParentElementId;}
this.set_itemTemplateParentElementId =function(id){_itemTemplateParentElementId =id;this.raisePropertyChanged('itemTemplateParentElementId');}
this.get_layoutTemplate =function(){return _layoutTemplate;}
this.set_layoutTemplate =function(template){if (_layoutTemplate){_layoutTemplate.dispose();}
_layoutTemplate =template;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('layoutTemplate');}
this.get_selectedItemCssClass =function(){return _selectedItemClass;}
this.set_selectedItemCssClass =function(value){if (value !=_selectedItemClass){_selectedItemClass =value;this.render();this.raisePropertyChanged('selectedItemCssClass');}
}
this.get_separatorCssClass =function(){return _separatorClass;}
this.set_separatorCssClass =function(value){if (value !=_separatorClass){_separatorClass =value;this.render();this.raisePropertyChanged('separatorCssClass');}
}
this.get_separatorTemplate =function(){return _separatorTemplate;}
this.set_separatorTemplate =function(template){if (_separatorTemplate){_separatorTemplate.dispose();}
_separatorTemplate =template;if (this.get_isUpdating()){this._renderPending =true;}
else {this.render();}
this.raisePropertyChanged('separatorTemplate');}
this.getDescriptor =function(){var td =Web.UI.Data.ListView.callBaseMethod(this,'getDescriptor');td.addProperty("alternatingItemCssClass",String);td.addProperty("layoutTemplate",Web.UI.ITemplate);td.addProperty("itemCssClass",String);td.addProperty("itemTemplate",Web.UI.ITemplate);td.addProperty("itemTemplateParentElementId",String);td.addProperty("selectedItemCssClass",String);td.addProperty("separatorCssClass",String);td.addProperty("separatorTemplate",Web.UI.ITemplate);td.addProperty("emptyTemplate",Web.UI.ITemplate);return td;}
Web.UI.Data.ListView.registerBaseMethod(this,'getDescriptor');this.getItemElement =function(index){return _itemElements[index];}
this.initialize =function(){_focusHandler =Function.createDelegate(this,this._onGotFocus);_keyDownHandler =Function.createDelegate(this,this._onKeyDown);_itemFocusHandler =Function.createDelegate(this,this._onItemFocus);_itemClickHandler =Function.createDelegate(this,this._onItemClick);Web.UI.Data.ListView.callBaseMethod(this,'initialize');this.element.attachEvent('onkeydown',_keyDownHandler);this.element.attachEvent('onfocus',_focusHandler);if (_itemTemplate){_itemTemplate.initialize();}
if (_separatorTemplate){_separatorTemplate.initialize();}
if (_emptyTemplate){_emptyTemplate.initialize();}
if (_layoutTemplate){_layoutTemplate.initialize();}
if (!this.get_tabIndex()){this.set_tabIndex(0);}
this.render();}
Web.UI.Data.ListView.registerBaseMethod(this,'initialize');this.dispose =function(){if (this.element){this.element.detachEvent('onfocus',_focusHandler);this.element.detachEvent('onkeydown',_keyDownHandler);}
if (_itemElements){for (var i =_itemElements.length -1;i >=0;i--){_itemElements[i].detachEvent('onfocus',_itemFocusHandler);_itemElements[i].detachEvent('onclick',_itemClickHandler);}
}
if (_layoutTemplate){_layoutTemplate.dispose();_layoutTemplate =null;}
if (_itemTemplate){_itemTemplate.dispose();_itemTemplate =null;}
if (_separatorTemplate){_separatorTemplate.dispose();_separatorTemplate =null;}
if (_emptyTemplate){_emptyTemplate.dispose();_emptyTemplate =null;}
_itemElements =null;_separatorElements =null;Web.UI.Data.ListView.callBaseMethod(this,'dispose');}
Web.UI.Data.ListView.registerBaseMethod(this,'dispose');this._onGotFocus =function(){setFocus(this,this.getItemElement(this.get_dataIndex()));}
this._onKeyDown =function(){var e =window.event;if (e.srcElement ==this.getItemElement(_focusIndex)){if ((e.keyCode ==Web.UI.Key.Up)||(e.keyCode ==Web.UI.Key.Left)){if (_focusIndex >0){setFocus(this,this.getItemElement(_focusIndex -1));e.returnValue =false;}
}
else if ((e.keyCode ==Web.UI.Key.Down)||(e.keyCode ==Web.UI.Key.Right)){if (_focusIndex <(this.get_length()-1)){setFocus(this,this.getItemElement(_focusIndex +1));e.returnValue =false;}
}
else if ((e.keyCode ==Web.UI.Key.Return)||(e.keyCode ==Web.UI.Key.Space)){if (_focusIndex !=-1){this.set_dataIndex(_focusIndex);e.returnValue =false;}
}
}
}
this._onItemFocus =function(){_focusIndex =window.event.srcElement.dataIndex;}
this._onItemClick =function(){var s =window.event.srcElement;var srcTag =s.tagName.toUpperCase();while (s &&(typeof(s.dataIndex)=='undefined')){s =s.parentNode;}
if (s){var idx =s.dataIndex;sel =this.getItemElement(idx);if (sel){this.set_dataIndex(idx);if ((srcTag !="INPUT")&&(srcTag !="TEXTAREA")&&(srcTag !="SELECT")&&(srcTag !="BUTTON")&&(srcTag !="A")){setFocus(this,sel);}
}
}
}
this.render =function(){var i,element;for (i =_itemElements.length -1;i >=0;i--){element =_itemElements[i];if (element){Web.UI.ITemplate.disposeInstance(element);}
}
_itemElements =[];for (i =_separatorElements.length -1;i >=0;i--){element =_separatorElements[i];if (element){Web.UI.ITemplate.disposeInstance(element);}
}
_separatorElements =[];if (this.element.childNodes.length){Web.UI.ITemplate.disposeInstance(this.element);}
this.element.innerHTML ='';var items =this.get_data();var itemLength =items ?items.get_length():0;if (itemLength >0){var template =this.get_layoutTemplate();if (template){var itemTemplate =this.get_itemTemplate();var separatorTemplate =this.get_separatorTemplate();var layoutTemplateInstance =template.createInstance(this.element,null,findItemTemplateParentCallback,_itemTemplateParentElementId);var itemTemplateParent =layoutTemplateInstance.callbackResult;var lengthm1 =itemLength -1;for (i =0;i <itemLength;i++){var item =items.getItem(i);if (itemTemplate){element =itemTemplate.createInstance(itemTemplateParent,item).instanceElement;if (_itemClass){if ((i %2 ==1)&&(_alternatingItemClass)){element.className =_alternatingItemClass;}
else {element.className =_itemClass;}
}
_itemElements[i]=element;element.tabIndex =-1;element.dataIndex =i;element.attachEvent('onfocus',_itemFocusHandler);element.attachEvent('onclick',_itemClickHandler);}
if (separatorTemplate &&(i !=lengthm1)&&itemTemplateParent){var sep =separatorTemplate.createInstance(itemTemplateParent).instanceElement;if (_separatorClass){sep.className =_separatorClass;}
_separatorElements[i]=sep;}
}
}
}
else {var emptyTemplate =this.get_emptyTemplate();if (emptyTemplate){emptyTemplate.createInstance(this.element);}
}
this._renderPending =false;}
function findItemTemplateParentCallback(instanceElement,markupContext,id){return markupContext.findObject(id,true);}
function setFocus(owner,element){if (element.focus){for(var i =owner.get_length()-1;i >=0;i--){var sel =owner.getItemElement(i);if (sel){sel.tabIndex =-1;}
}
var t =owner.element.tabIndex;if (t ==-1){t =owner.element.__tabIndex;}
element.tabIndex =t;setTimeout(Function.createCallback(focus,element),0);owner.element.__tabIndex =t;owner.element.tabIndex =-1;}
}
function focus(element){element.focus();}
}
Type.registerClass('Web.UI.Data.ListView',Web.UI.Data.DataControl);Web.TypeDescriptor.addType('script','listView',Web.UI.Data.ListView);Type.registerNamespace('Web.WebForms');Web.WebForms.PostBackAction =function(){Web.WebForms.PostBackAction.initializeBase(this);var _eventArgument;this.get_eventArgument =function(){return _eventArgument;}
this.set_eventArgument =function(value){_eventArgument =value;}
this.getDescriptor =function(){var td =Web.WebForms.PostBackAction.callBaseMethod(this,'getDescriptor');td.addProperty('eventArgument',String);td.addProperty('target',String);return td;}
this.performAction =function(){__doPostBack(this.get_target(),this.get_eventArgument());}
}
Type.registerSealedClass('Web.WebForms.PostBackAction',Web.Action);Web.TypeDescriptor.addType('script','postBack',Web.WebForms.PostBackAction);Web.WebForms._PageRequest =new function(){}
Web.WebForms._PageRequest._form =null;Web.WebForms._PageRequest._scriptManagerID =null;Web.WebForms._PageRequest._additionalInput =null;Web.WebForms._PageRequest._onsubmit =null;Web.WebForms._PageRequest._originalDoPostBack =null;Web.WebForms._PageRequest._request =null;Web.WebForms._PageRequest._referencedScripts =[];Web.WebForms._PageRequest._scriptsToLoad =null;Web.WebForms._PageRequest._currentLoadingScript =null;Web.WebForms._PageRequest._XMLScript =null;Web.WebForms._PageRequest.get_inPostBack =function(){return Web.WebForms._PageRequest._request !=null;}
Web.WebForms._PageRequest.abortPostBack =function(){if (Web.WebForms._PageRequest.get_inPostBack()){Web.WebForms._PageRequest._request.abort();Web.WebForms._PageRequest._request.dispose();Web.WebForms._PageRequest._request =null;}
}
Web.WebForms._PageRequest._doPostBack =function(eventTarget,eventArgument){Web.WebForms._PageRequest._additionalInput =null;if (Web.WebForms._PageRequest.get_inPostBack()){if (window.event){window.event.returnValue =false;}
return;}
var form =Web.WebForms._PageRequest._form;form.__EVENTTARGET.value =eventTarget;form.__EVENTARGUMENT.value =eventArgument;Web.WebForms._PageRequest._onFormSubmit();if (window.event){window.event.returnValue =false;}
}
Web.WebForms._PageRequest._loadScript =function(){var currentScript =Web.WebForms._PageRequest._currentLoadingScript;if (currentScript){if ((currentScript.readyState !='loaded')&&(currentScript.readyState !='complete')){return;}
else {if (Web.Application.get_type()!=Web.ApplicationType.InternetExplorer){currentScript.onload =null;}
else {currentScript.onreadystatechange =null;}
Web.WebForms._PageRequest._currentLoadingScript =null;}
}
var scripts =Web.WebForms._PageRequest._scriptsToLoad;if (scripts &&(scripts.length >1)){var scriptSrc =scripts.dequeue();var scriptElement =document.createElement('SCRIPT');Web.WebForms._PageRequest._currentLoadingScript =scriptElement;if (Web.Application.get_type()!=Web.ApplicationType.InternetExplorer){scriptElement.readyState ='loaded';scriptElement.onload =Web.WebForms._PageRequest._loadScript;}
else {scriptElement.onreadystatechange =Web.WebForms._PageRequest._loadScript;}
scriptElement.type ='text/javascript';scriptElement.src =scriptSrc;var headElement =document.getElementsByTagName('HEAD')[0];headElement.appendChild(scriptElement);return;}
var scriptText =scripts[0];if (scriptText){var scriptElement =document.createElement('SCRIPT');scriptElement.type ='text/javascript';scriptElement.text =scriptText;var headElement =document.getElementsByTagName('HEAD')[0];headElement.appendChild(scriptElement);}
Web.WebForms._PageRequest._onFormSubmitCompletedCallback();}
Web.WebForms._PageRequest._onFormElementClick =function(){var element =window.event.srcElement;if (element.disabled){return;}
if (Web.WebForms._PageRequest.get_inPostBack()){return;}
if (element.tagName =='INPUT'){var type =element.type;if (type =='submit'){Web.WebForms._PageRequest._additionalInput =element.name +'='+encodeURIComponent(element.value);}
else if (type =='image'){var x =window.event.offsetX;var y =window.event.offsetY;Web.WebForms._PageRequest._additionalInput =element.name +'.x='+x +'&'+element.name +'.y='+y;}
}
else if ((element.tagName =='BUTTON')&&(element.name.length !=0)&&(element.type =='submit')){Web.WebForms._PageRequest._additionalInput =element.name +'='+encodeURIComponent(element.value);}
}
Web.WebForms._PageRequest._onFormSubmit =function(){if (Web.WebForms._PageRequest.get_inPostBack()){if (window.event){window.event.returnValue =false;}
return false;}
var continueSubmit =true;if (Web.WebForms._PageRequest._onsubmit){continueSubmit =Web.WebForms._PageRequest._onsubmit();}
if (!continueSubmit){if (window.event){window.event.returnValue =false;}
return false;}
var form =Web.WebForms._PageRequest._form;if (form.action !=form._initialAction){return true;}
var formBody =new Web.StringBuilder();formBody.append(Web.WebForms._PageRequest._scriptManagerID +'=Update&');var count =form.elements.length;for (var i =0;i <count;i++){var element =form.elements[i];var name =element.name;if ((name ==null)||(name.length ==0)){continue;}
var tagName =element.tagName;if (tagName =='INPUT'){var type =element.type;if ((type =='text')||(type =='password')||(type =='hidden')||(((type =='checkbox')||(type =='radio'))&&element.checked)){formBody.append(name);formBody.append('=');formBody.append(encodeURIComponent(element.value));formBody.append('&');}
}
else if (tagName =='SELECT'){var optionCount =element.options.length;for (var j =0;j <optionCount;j++){var option =element.options[j];if (option.selected ==true){formBody.append(name);formBody.append('=');formBody.append(encodeURIComponent(option.value));formBody.append('&');}
}
}
else if (tagName =='TEXTAREA'){formBody.append(name);formBody.append('=');formBody.append(encodeURIComponent(element.value));formBody.append('&');}
}
if (Web.WebForms._PageRequest._additionalInput){formBody.append(Web.WebForms._PageRequest._additionalInput);Web.WebForms._PageRequest._additionalInput =null;}
var request =new Web.Net.WebRequest();request.set_url(form.action);request.get_headers()['delta']='true';request.get_headers()['Cache-Control']='no-cache';request.set_timeoutInterval(90000);request.completed.add(Web.WebForms._PageRequest._onFormSubmitCompleted);request.timeout.add(Web.WebForms._PageRequest._onFormSubmitTimeout);request.set_body(formBody.toString());Web.WebForms._PageRequest._request =request;request.invoke();if (window.event){window.event.returnValue =false;}
return false;}
Web.WebForms._PageRequest._onFormSubmitCompleted =function(sender,eventArgs){var response =sender.get_response();var delta =response.get_xml();if (Web.Application.get_type()==Web.ApplicationType.InternetExplorer){delta.setProperty('SelectionLanguage','XPath');}
var deltaPanels =delta.selectSingleNode("/delta/deltaPanels/text()");if (deltaPanels &&deltaPanels.length){deltaPanels =deltaPanels.nodeValue.split(',');for (var i =0;i <deltaPanels.length;i++){var deltaPanelID =deltaPanels[i];var deltaPanelRendering =delta.selectSingleNode('/delta/rendering//span[@id="'+deltaPanelID +'"]');deltaPanelRendering =deltaPanelRendering.firstChild.nodeValue;Web.WebForms._PageRequest._updatePanel(deltaPanelID,deltaPanelRendering);}
}
var hiddenFields =delta.selectNodes('/delta/rendering//input[@type="hidden"]');for (var i =0;i <hiddenFields.length;i++){var id =hiddenFields[i].attributes.getNamedItem('id').nodeValue;var value =hiddenFields[i].attributes.getNamedItem('value').nodeValue;document.getElementById(id).value =value;}
var title =delta.selectSingleNode('/delta/rendering//title/text()');document.title =title.nodeValue.trim();var styleSheetMarkup =delta.selectSingleNode('/delta/rendering/head/style[position()=last()]');if (styleSheetMarkup){Web.WebForms._PageRequest._updateStyleSheet(styleSheetMarkup.text);}
Web.WebForms._PageRequest._XMLScript =delta.selectSingleNode('/delta/xmlScript');var scripts =delta.selectNodes('/delta/rendering//script[@type="text/javascript"]');if (scripts &&scripts.length){Web.WebForms._PageRequest._updateScripts(scripts);}
else {Web.WebForms._PageRequest._onFormSubmitCompletedCallback();}
}
Web.WebForms._PageRequest._onFormSubmitCompletedCallback =function(){if (Web.WebForms._PageRequest._XMLScript){Web.Application._update(Web.WebForms._PageRequest._XMLScript.childNodes[0]);Web.WebForms._PageRequest._XMLScript =null;}
Web.WebForms._PageRequest._request.dispose();Web.WebForms._PageRequest._request =null;Web.WebForms._PageRequest._scriptsToLoad =null;Web.WebForms._PageRequest._currentLoadingScript =null;Web.WebForms._PageRequest._additionalInput =null;}
Web.WebForms._PageRequest._onFormSubmitTimeout =function(sender,eventArgs){Web.WebForms._PageRequest._request.dispose();Web.WebForms._PageRequest._request =null;}
Web.WebForms._PageRequest._setupAsyncPostBacks =function(form,scriptManagerID){Web.WebForms._PageRequest._form =form;Web.WebForms._PageRequest._scriptManagerID =scriptManagerID;form._initialAction =form.action;Web.WebForms._PageRequest._onsubmit =form.onsubmit;form.onsubmit =null;form.attachEvent('onsubmit',Web.WebForms._PageRequest._onFormSubmit);form.attachEvent('onclick',Web.WebForms._PageRequest._onFormElementClick);Web.WebForms._PageRequest._originalDoPostBack =window.__doPostBack;if (Web.WebForms._PageRequest._originalDoPostBack){window.__doPostBack =Web.WebForms._PageRequest._doPostBack;}
}
Web.WebForms._PageRequest._updatePanel =function(panelID,rendering){var contentPreElement =document.getElementById(panelID +'_Start');var contentPostElement =document.getElementById(panelID +'_End');var elementsToDestroy =[];var nextSibling =contentPreElement.nextSibling;while (nextSibling !=contentPostElement){elementsToDestroy.add(nextSibling);nextSibling =nextSibling.nextSibling;}
var parentNode =contentPreElement.parentNode;for (var j =0;j <elementsToDestroy.length;j++){if (elementsToDestroy[j].control){elementsToDestroy[j].control.dispose();}
parentNode.removeChild(elementsToDestroy[j]);}
if (Web.Application.get_type()==Web.ApplicationType.InternetExplorer){contentPreElement.insertAdjacentHTML('afterEnd',rendering);}
else {var r =contentPreElement.ownerDocument.createRange();r.setStartBefore(contentPreElement);var parsedNode =r.createContextualFragment(rendering);if (contentPreElement.nextSibling){parentNode.insertBefore(parsedNode,contentPreElement.nextSibling);}
else {parentNode.appendChild(parsedNode);}
}
}
Web.WebForms._PageRequest._updateScripts =function(scripts){var existingScripts =document.getElementsByTagName('SCRIPT');for (var i =existingScripts.length -1;i >=0;i--){var scriptNode =existingScripts[i];var srcAttribute =scriptNode.attributes.getNamedItem('src');var src =(srcAttribute)?srcAttribute.nodeValue :'';if (src.length){if (src.indexOf('/WebResource.axd?')>=0){var indexT =src.indexOf('&t=');src =src.substring(0,indexT -1);}
if (!Web.WebForms._PageRequest._referencedScripts.contains(src)){Web.WebForms._PageRequest._referencedScripts.add(src);}
}
scriptNode.parentNode.removeChild(scriptNode);}
var scriptsToLoad =[];var scriptText ='';for (var i =0;i <scripts.length;i++){var xmlScriptNode =scripts[i];var srcAttribute =xmlScriptNode.attributes.getNamedItem('src');var src =(srcAttribute)?srcAttribute.nodeValue :'';if (src.length){if (src.indexOf('/WebResource.axd?')>=0){var indexT =src.indexOf('&t=');src =src.substring(0,indexT -1);}
if (Web.WebForms._PageRequest._referencedScripts.contains(src)){continue;}
scriptsToLoad.queue(src);}
else {var text;if (xmlScriptNode.childNodes.length !=0){for (var c =xmlScriptNode.childNodes.length -1;c >=0;c--){if (xmlScriptNode.childNodes[c].nodeType ==8){text =xmlScriptNode.childNodes[c].nodeValue;break;}
}
}
else {text =xmlScriptNode.nodeValue;}
if (text){if (text.indexOf('function __doPostBack(')>=0){continue;}
scriptText +=text;}
}
}
scriptsToLoad.queue(scriptText);if (scriptsToLoad.length !=0){Web.WebForms._PageRequest._scriptsToLoad =scriptsToLoad;Web.WebForms._PageRequest._currentLoadingScript =null;Web.WebForms._PageRequest._loadScript();}
else {Web.WebForms._PageRequest._onFormSubmitCompletedCallback();}
}
Web.WebForms._PageRequest._updateStyleSheet =function(cssText){var head =document.getElementsByTagName('HEAD')[0];var styles =document.styleSheets;var styleSheet =styles[styles.length -1];if (Web.Application.get_type()==Web.ApplicationType.InternetExplorer){styleSheet.cssText =cssText;}
else {for (var i =styleSheet.cssRules.length -1;i >=0;i--){styleSheet.deleteRule(i);}
var ruleLines =cssText.split('}');for (var i =0;i <ruleLines.length;i++){var rule =ruleLines[i];var index =rule.indexOf('{');var style =rule.substr(index +1).trim();if (style.length !=0){var selector =rule.substring(0,index -1).trim();styleSheet.insertRule(selector +'{'+style +'}',styleSheet.cssRules.length);}
}
}
}
