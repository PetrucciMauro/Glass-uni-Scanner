//=================
// get the packages
// ================
var express    = require('express');
var app        = express();
var bodyParser = require('body-parser');
var morgan     = require('morgan');

var jwt    = require('jsonwebtoken');
var config = require('./config');
var User   = require('./models/user');
var multer  = require('multer')
var fs = require('fs');


//==============
// configuration
//==============

var port = process.env.PORT || 8080;
app.set('database', config.database);
app.set('SuperSecret', config.secret);

app.use(bodyParser.urlencoded({ extended: false}));
app.use(bodyParser.json());

app.use(morgan('dev')); // log to console

var MongoClient = require('mongodb').MongoClient;
var ObjectID = require('mongodb').ObjectID

//===============
// authentication
//===============

app.get('/', function(req, res) {
        res.send('Wellcome! to get a public file: /publicpages, account staff: /account, private services: /private'
																	);
								});

app.get('/account', function(req, res) {
								res.send('to register: ~/register, to authenticate: ~/authenticate, to change password: ~/changepassword');
								});

app.get('/account/authenticate', function(req, res) {
        var header=req.headers['authorization']||'null';
        parts=header.split(/:/);
        user=parts[0];
        pass=parts[1];
        
        MongoClient.connect(app.get('database'), function(err, db) {
                            if(err) throw err;
                            
                            db.collection('users').findOne({'username': user, 'password': pass}, function(err, doc) {
                                                           if(err) throw err;
                                                           if(doc == null){
                                                           db.close();
                                                           res.status(400);
                                                           res.json({
																																																																				success: false,
																																																																				message: 'Username or password incorrect'
																																																																				});
                                                           }
                                                           else{
                                                           var token = jwt.sign({user: user}, app.get('SuperSecret'), {
                                                                                expiresInMinutes: 1440 // expires in 24 hours
                                                                                });
                                                           
                                                           res.writeHead(200, {"Content-Type": "application/json", "authorization": token});
                                                           var json = JSON.stringify({
                                                                                     success: true,
                                                                                     message: 'Enjoy your token!',
                                                                                     });
                                                           res.end(json);
                                                           }
																																																											});
                            
                            console.dir('called findOne()');
																												});

								});

app.post('/account/register', function(req, res) {
         var header=req.headers['authorization']||'null';
         parts=header.split(/:/);
         user=parts[0];
         pass=parts[1];
         
         MongoClient.connect(app.get('database'), function(err, db) {
																													if(err) throw err;
																													db.collection('users').findOne({'username': user}, function(err, doc) {
																																																												if(err) throw err;
																																																												if(doc == null){
																																																												db.collection('users').insert({'username': user, 'password': pass}, function(err, doc){
																																																																																										if(err) throw err;
																																																																																										console.dir('called insert()');
																																																																																										res.json({
																																																																																																			success: true,
																																																																																																			message: 'User '+user+' registered'
																																																																																																			});
																																																																																										fs.mkdirSync(__dirname+'/files/'+user);
																																																																																										fs.mkdirSync(__dirname+'/files/'+user+'/image');
																																																																																										fs.mkdirSync(__dirname+'/files/'+user+'/video');
																																																																																										fs.mkdirSync(__dirname+'/files/'+user+'/audio');
																																																																																										});
																																																												}
																																																												else{
																																																												res.status(400);
																																																												res.json({
																																																																					success: false,
																																																																					message: 'Username already registered'
																																																																					});
																																																												}
																																																												
																																																												});
																													});
									});

app.post('/account/changepassword', function(req, res) {
         var header=req.headers['authorization']||'null';
         parts=header.split(/:/);
         user=parts[0];
         pass=parts[1];
									passNew=parts[2];
         
         MongoClient.connect(app.get('database'), function(err, db) {
																													if(err) throw err;
																													db.collection('users').findOne({'username': user, 'password': pass}, function(err, doc) {
																																																												if(err) throw err;
																																																												if(doc != null){
																																																												db.collection('users').update({'username': user}, {$set: {'password' : passNew }}, function(err, doc){
																																																																																										if(err) throw err;
																																																																																										console.dir('called udpate()');
																																																																																										res.json({
																																																																																																			success: true,
																																																																																																			message: 'Password updated'
																																																																																																			});
																																																																																										});
																																																												}
																																																												else{
																																																												res.status(400);
																																																												res.json({
																																																																					success: false,
																																																																					message: 'Username or password not correct'
																																																																					});
																																																												}
																																																												
																																																												});
																													});
									});

//==================
// htmlpages_server
//==================

app.use('/publicpages', express.static('public_html'));

app.use('/private/htdocs', express.static('private_html'));


//==================
// token_middleware
//==================

var privateRoutes = express.Router();
app.use('/private', privateRoutes);

privateRoutes.use(function(req, res, next) {
																		
																		var token=req.headers['authorization'];
																		if (token) {
																		
																		// verifies secret and checks exp
																		jwt.verify(token, app.get('SuperSecret'), function(err, decoded) {
																													if (err) {
																													res.status(400);
																													return res.json({ success: false, message: 'Failed to authenticate token' });
																													} else {
																													// save the token
																													req.user = decoded.user;
																													next();
																													}
																													});
																		} else {
																		return res.status(403).send({
																																														success: false,
																																														message: 'No token provided.'
																																														});
																		}
																		});


//==================
// files_server
//==================


var filesRoutes = express.Router();
app.use('/private/api/files', filesRoutes);

filesRoutes.get('/image', function(req, res){ // scorri tutti i file nella cartella e ritorna una json dei nomi
																var file_names = fs.readdirSync(__dirname+'/files/'+req.user+'/image');
																res.json({
																									success: true,
																									message: 'correctly get files names',
																									names: file_names
																									});
																});

filesRoutes.get('/video', function(req, res){
																var file_names = fs.readdirSync(__dirname+'/files/'+req.user+'/video');
																res.json({
																									success: true,
																									message: 'correctly get files names',
																									names: file_names
																									});
																});

filesRoutes.get('/audio', function(req, res){
																var file_names = fs.readdirSync(__dirname+'/files/'+req.user+'/audio');
																res.json({
																									success: true,
																									message: 'correctly get files names',
																									names: file_names
																									});
																});
//======
//delete

filesRoutes.delete('/image/[^/]+', function(req, res){
																			var dir= __dirname+'/files/'+req.user+'/image/';
																			var name = req.originalUrl.split("/")[5];
																			var there_is = fs.existsSync(dir+name);
																			
																			if(there_is){
																			fs.unlinkSync(dir+name);
																			res.json({
																												success: true,
																												message: 'correctly delete file '+dir+name
																												});

																			}
																			else{
																			res.json({
																												success: false,
																												message: 'file '+dir+name+' does not exists'
																												});
																			}
																			
																			});

filesRoutes.delete('/video/[^/]+', function(req, res){
																			var dir= __dirname+'/files/'+req.user+'/video/';
																			var name = req.originalUrl.split("/")[5];
																			var there_is = fs.existsSync(dir+name);
																			
																			if(there_is){
																			fs.unlinkSync(dir+name);
																			res.json({
																												success: true,
																												message: 'correctly delete file '+dir+name
																												});
																			
																			}
																			else{
																			res.json({
																												success: false,
																												message: 'file '+dir+name+' does not exists'
																												});
																			}
																			
																			});

filesRoutes.delete('/audio/[^/]+', function(req, res){
																			var dir= __dirname+'/files/'+req.user+'/audio/';
																			var name = req.originalUrl.split("/")[5];
																			var there_is = fs.existsSync(dir+name);
																			
																			if(there_is){
																			fs.unlinkSync(dir+name);
																			res.json({
																												success: true,
																												message: 'correctly delete file '+dir+name
																												});
																			
																			}
																			else{
																			res.json({
																												success: false,
																												message: 'file '+dir+name+' does not exists'
																												});
																			}
																			
																			});
//====
// get

filesRoutes.get('/image/[^/]+', function (req, res) {
																
																var options = {
																root: __dirname + '/files/'+req.user+'/image',
																dotfiles: 'deny',
																headers: {
																'x-timestamp': Date.now(),
																'x-sent': true
																}
																};
								
																var file_name = req.originalUrl.split("/")[5];
																var there_is = fs.existsSync(__dirname+'/files/'+req.user+'/image/'+file_name);

																if(there_is == false){
																res.status(404).send({
																																					success: false,
																																					message: 'File not found'
																																					});
																}
																else{
																res.sendFile(file_name, options, function (err) {
																													if (err) {
																													console.log(err);
																													res.status(err.status).end();
																													}
																													else {
																													console.log('Sent:', file_name);
																													}
																													});
																}
																});


filesRoutes.get('/audio/[^/]+', function (req, res) {
																
																var options = {
																root: __dirname + '/files/'+req.user+'/audio',
																dotfiles: 'deny',
																headers: {
																'x-timestamp': Date.now(),
																'x-sent': true
																}
																};
																
																var file_name = req.originalUrl.split("/")[5];
																var there_is = fs.existsSync(__dirname+'/files/'+req.user+'/audio/'+file_name);
																
																if(there_is == false){
																res.status(404).send({
																																					success: false,
																																					message: 'File not found'
																																					});
																}
																else{
																res.sendFile(file_name, options, function (err) {
																													if (err) {
																													console.log(err);
																													res.status(err.status).end();
																													}
																													else {
																													console.log('Sent:', file_name);
																													}
																													});
																}
																});


filesRoutes.get('/video/[^/]+', function (req, res) {
																
																var options = {
																root: __dirname + '/files/'+req.user+'/video',
																dotfiles: 'deny',
																headers: {
																'x-timestamp': Date.now(),
																'x-sent': true
																}
																};
																
																var file_name = req.originalUrl.split("/")[5];
																var there_is = fs.existsSync(__dirname+'/files/'+req.user+'/video/'+file_name);
																
																if(there_is == false){
																res.status(404).send({
																																					success: false,
																																					message: 'File not found'
																																					});
																}
																else{
																res.sendFile(file_name, options, function (err) {
																													if (err) {
																													console.log(err);
																													res.status(err.status).end();
																													}
																													else {
																													console.log('Sent:', file_name);
																													}
																													});
																}
																});


//=====
// post

filesRoutes.post('/image/[^/]+',[ multer({
																																									dest: __dirname+'/files/',
																																									
																																									changeDest: function(dest, req, res) {
																																									var newDestination = dest + req.user + '/image';
																																									return newDestination;
																																									},
																																									
																																									rename: function (fieldname, filename, req, res) {
																																									var new_name = req.originalUrl.split("/")[5];
																																									return new_name; }
																																									
																																									}),
																																	function(req, res){
																																	console.log(req.body) // form fields
																																	console.log(req.files) // form files
																																	res.status(204).end()
																																	}]);

filesRoutes.post('/audio/[^/]+',[ multer({
																																									dest: __dirname+'/files/',
																																									
																																									changeDest: function(dest, req, res) {
																																									var newDestination = dest + req.user + '/audio';
																																									return newDestination;
																																									},
																																									
																																									rename: function (fieldname, filename, req, res) {
																																									var new_name = req.originalUrl.split("/")[5];
																																									return new_name; }
																																									
																																									}),
																																	function(req, res){
																																	console.log(req.body) // form fields
																																	console.log(req.files) // form files
																																	res.status(204).end()
																																	}]);

filesRoutes.post('/video/[^/]+',[ multer({
																																									dest: __dirname+'/files/',
																																									
																																									changeDest: function(dest, req, res) {
																																									var newDestination = dest + req.user + '/video';
																																									return newDestination;
																																									},
																																									
																																									
																																									rename: function (fieldname, filename, req, res) {
																																									var new_name = req.originalUrl.split("/")[5];
																																									return new_name; }
																																									
																																									}),
																																	function(req, res){
																																	console.log(req.body) // form fields
																																	console.log(req.files) // form files
																																	res.status(204).end()
																																	}]);

//=======
// rename

filesRoutes.post('/image/[^/]+/[^/]+', function(req, res){
								
									var dir= __dirname+'/files/'+req.user+'/image/';
									var name = req.originalUrl.split("/")[5];
									var new_name = req.originalUrl.split("/")[6];
									var there_is = fs.existsSync(dir+name);
									if(there_is){
									fs.renameSync(dir+name, dir+new_name);
									res.json({
																		success: true,
																		message: 'correctly renamed file '+dir+name+' in '+dir+new_name
																		});
									
									}
									else{
									res.json({
																		success: false,
																		message: 'file '+dir+name+' does not exists'
																		});
									}
									});

filesRoutes.post('/audio/[^/]+/[^/]+', function(req, res){
																	
																	var dir= __dirname+'/files/'+req.user+'/audio/';
																	var name = req.originalUrl.split("/")[5];
																	var new_name = req.originalUrl.split("/")[6];
																	var there_is = fs.existsSync(dir+name);
																	if(there_is){
																	fs.renameSync(dir+name, dir+new_name);
																	res.json({
																										success: true,
																										message: 'correctly renamed file '+dir+name+' in '+dir+new_name
																										});
																	
																	}
																	else{
																	res.json({
																										success: false,
																										message: 'file '+dir+name+' does not exists'
																										});
																	}
																	});

filesRoutes.post('/video/[^/]+/[^/]+', function(req, res){
																	
																	var dir= __dirname+'/files/'+req.user+'/video/';
																	var name = req.originalUrl.split("/")[5];
																	var new_name = req.originalUrl.split("/")[6];
																	var there_is = fs.existsSync(dir+name);
																	if(there_is){
																	fs.renameSync(dir+name, dir+new_name);
																	res.json({
																										success: true,
																										message: 'correctly renamed file '+dir+name+' in '+dir+new_name
																										});
																	
																	}
																	else{
																	res.json({
																										success: false,
																										message: 'file '+dir+name+' does not exists'
																										});
																	}
																	});


//=====================
// presentations_server
//=====================

var presentationRoutes = express.Router();
app.use('/private/api/presentations', presentationRoutes);

presentationRoutes.get('/', function(req, res){
																							
																							MongoClient.connect(app.get('database'), function(err, db) {
																																											if(err) throw err;
																																											
																																											db.collection('presentations'+req.user).find().toArray(function(err, doc){
																																																																																																		if(err) throw err;
																																																																																																		message = [];
																																																																																																		doc.forEach(function(pres){
																																																																																																														message.push(pres.meta);
																																																																																																														});
																																																																																																		
																																																																																																		res.json({
																																																																																																											success: true,
																																																																																																											message: message
																																																																																																											});
																																																																																																		db.close();

																																																																																																		});
																																											});
																							});


presentationRoutes.get('/[^/]+', function(req, res){
																							
																							MongoClient.connect(app.get('database'), function(err, db) {
																																											if(err) throw err;
																																											var id_pres = req.originalUrl.split("/")[4];
																																											var objectId = new ObjectID(id_pres);
																																											db.collection('presentations'+req.user).findOne({ '_id': objectId }, function(err, doc){
																																																																																											if(err) throw err;
																																																																																											
																																																																																											res.json({
																																																																																																				success: true,
																																																																																																				message: doc
																																																																																																				});
																																																																																											db.close();
																																																																																											
																																																																																											});
																																											});
																							});

presentationRoutes.delete('/[^/]+', function(req, res){
																							
																							MongoClient.connect(app.get('database'), function(err, db) {
																																											if(err) throw err;
																																											var id_pres = req.originalUrl.split("/")[4];
																																											var objectId = new ObjectID(id_pres);
																																											db.collection('presentations'+req.user).remove({ '_id': objectId }, function(err, removed){
																																																																																										if(err) throw err;
																																																																																										
																																																																																										res.json({
																																																																																																			success: true,
																																																																																																			message: 'removed presentation _id: '+id_pres
																																																																																																			});
																																																																																										db.close();
																																																																																										
																																																																																										});
																																											});
																										});

presentationRoutes.post('/new/[^/]+', function(req, res){
																										
																										MongoClient.connect(app.get('database'), function(err, db) {
																																														if(err) throw err;
																																														var name_pres = req.originalUrl.split("/")[5];
																																														var new_presentation = {'meta': {'name': name_pres}, 'proper': {} };
																																														db.collection('presentations'+req.user).insert(new_presentation, function(err, result){
																																																																																													if(err) throw err;
																																																																																													res.json({
																																																																																																						success: true,
																																																																																																						message: 'inserted presentation',
																																																																																																						id_pres: result.ops[0]._id.toString()
																																																																																																						});
																																																																																													db.close();
																																																																																													});
																																														});
																								});

presentationRoutes.post('/new/[^/]+/[^/]+', function(req, res){
																								
																								MongoClient.connect(app.get('database'), function(err, db) {
																																												if(err) throw err;
																																												var name_pres = req.originalUrl.split("/")[5];
																																												var id_tocopy = req.originalUrl.split("/")[6];
																																												var objectId = new ObjectID(id_tocopy);
																																												db.collection('presentations'+req.user).findOne({ '_id': objectId }, function(err, doc){
																																																																																												if(err) throw err;
																																																																																												var new_presentation = doc;
																																																																																												new_presentation.meta.name = name_pres;
																																																																																												delete new_presentation._id;
																																																																																												db.collection('presentations'+req.user).insert(new_presentation, function(err, result){
																																																																																																																																											if(err) throw err;
																																																																																																																																											res.json({
																																																																																																																																																				success: true,
																																																																																																																																																				message: 'inserted presentation',
																																																																																																																																																				id_pres: result.ops[0]._id.toString()
																																																																																																																																																				});
																																																																																																																																											db.close();
																																																																																																																																											});
																																																																																												});

																																																																																												
																																												
																																																																																												
																																												});
																								});

presentationRoutes.post('/[^/]+/rename/[^/]+', function(req, res){
																										
																										MongoClient.connect(app.get('database'), function(err, db) {
																																														if(err) throw err;
																																														var id_pres = req.originalUrl.split("/")[4];
																																														var name_pres = req.originalUrl.split("/")[5];

																																														var objectId = new ObjectID(id_pres);
																																														db.collection('presentations'+req.user).update({ '_id': objectId }, {$set: { 'meta.name' : name_pres }}, function(err, doc){
																																																																																													if(err) throw err;

																																																																																													res.json({
																																																																																																						success: true,
																																																																																																						message: 'renamed presentation: '+name_pres
																																																																																																						});
																																																																																													db.close();
																																																																																													
																																																																																													});
																																														});
																								});

presentationRoutes.delete('/[^/]+/delete/[^/]+/[^/]+', function(req, res){
																								
																								MongoClient.connect(app.get('database'), function(err, db) {
																																												if(err) throw err;
																																												var id_pres = req.originalUrl.split("/")[4];
																																												var type_element = req.originalUrl.split("/")[6];
																																												var id_element = req.originalUrl.split("/")[7];
																																												
																																												var objectId_pres = new ObjectID(id_pres);
																																												var field_path;
																																												
																																												switch(type_element) {
																																												case 'text':
																																												field_path = 'proper.texts';
																																												break;
																																												case 'frame':
																																												field_path = 'proper.frames';
																																												case 'image':
																																												field_path = 'proper.images';
																																												break;
																																												case 'SVG':
																																												field_path = 'proper.SVGs';
																																												break;
																																												case 'audio':
																																												field_path = 'proper.audios';
																																												break;
																																												case 'video':
																																												field_path = 'proper.videos';
																																												break;
																																												case 'background':
																																												field_path = 'proper.background';
																																												break;
																																												default:
																																												res.json({
																																																					success: true,
																																																					message: 'element type: '+type_element+' not known'
																																																					});
																																												return;
																																												}
																																												
																																												db.collection('presentations'+req.user).update({'_id': objectId_pres}, {$pull : {field_path : {"id" : id_element}}}, function(err, doc){
																																																																																											if(err) throw err;
																																																																																											res.json({
																																																																																																				success: true,
																																																																																																				message: 'deleted element'
																																																																																																				});
																																																																																											db.close();
																																																																																											});
																																												});
																								});

//to test
presentationRoutes.put('/[^/]+/element', function(req, res){
																										
																										MongoClient.connect(app.get('database'), function(err, db) {
																																														if(err) throw err;
																																														var id_pres = req.originalUrl.split("/")[4];
																																														var id_element = req.body.id;
																																														
																																														var objectId_pres = new ObjectID(id_pres);
																																														var new_element = req.body.element;
																																														
																																														var field_path;
																																														
																																														switch(new_element.type) {
																																														case 'text':
																																														field_path = 'proper.texts';
																																														break;
																																														case 'frame':
																																														field_path = 'proper.frames';
																																														case 'image':
																																														field_path = 'proper.images';
																																														break;
																																														case 'SVG':
																																														field_path = 'proper.SVGs';
																																														break;
																																														case 'audio':
																																														field_path = 'proper.audios';
																																														break;
																																														case 'video':
																																														field_path = 'proper.videos';
																																														break;
																																														case 'background':
																																														field_path = 'proper.background';
																																														break;
																																														default:
																																														res.json({
																																																							success: true,
																																																							message: 'element type: '+type_element+' not known'
																																																							});
																																														return;
																																														}
																																														var path_to_id_element = field_path+'.id';
																																														var path_to_element = field_path/*+'.$'*/;
																																														var to_set = {};
																																														to_set[path_to_element] = new_element;
																																														
																																														db.collection('presentations'+req.user).update({'_id': objectId_pres, path_to_id_element : id_element}, {$set: to_set }, function(err, doc){
																																																																																													if(err) throw err;
																																																																																													
																																																																																													res.json({
																																																																																																						success: true,
																																																																	 																																					message: 'element replaced'
																																																																																																						});
																																																																																													db.close();
																																																																																													});
																																														});
																							});


presentationRoutes.post('/[^/]+/element', function(req, res){
																							
																							MongoClient.connect(app.get('database'), function(err, db) {
																																											if(err) throw err;
																																											var id_pres = req.originalUrl.split("/")[4];
																																											var id_element = req.body.id;
																																											
																																											var objectId_pres = new ObjectID(id_pres);
																																											var new_element = req.body.element;
																																											if(new_element == null){ res.json({
																																																																												success: false,
																																																																												message: 'body.element not sent'
																																																																												});
																																											return;
																																											}
																																											
																																											var field_path;
																																											
																																											switch(new_element.type) {
																																											case 'text':
																																											field_path = 'proper.texts';
																																											break;
																																											case 'frame':
																																											field_path = 'proper.frames';
																																											case 'image':
																																											field_path = 'proper.images';
																																											break;
																																											case 'SVG':
																																											field_path = 'proper.SVGs';
																																											break;
																																											case 'audio':
																																											field_path = 'proper.audios';
																																											break;
																																											case 'video':
																																											field_path = 'proper.videos';
																																											break;
																																											case 'background':
																																											field_path = 'proper.background';
																																											break;
																																											default:
																																											res.json({
																																																				success: true,
																																																				message: 'element type: '+type_element+' not known'
																																																				});
																																											return;
																																											}
																																											var to_push = {};
																																											to_push[field_path] = new_element;
																																											
																																											db.collection('presentations'+req.user).update({'_id': objectId_pres}, {$push : to_push},{'upsert' : true},  function(err, doc){
																																																																																										if(err) throw err;
																																																																																										
																																																																																										res.json({
																																																																																																			success: true,
																																																																																																			message: 'element inserted '+new_element.type																																																																																																			});
																																																																																										db.close();
																																																																																										});
																																											});
																							});



//==================
// start the server
//==================

app.listen(port);
console.log('Server listening at http//localhost: ' + port );


