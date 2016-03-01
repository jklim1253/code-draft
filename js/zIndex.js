var PostManager = function() {
	var posts = [];
	function _push(id) {
		var exist = false;
		var index = posts.length;
		while (index--) {
			if (posts[index] === id) {
				exist = true;
				console.log("same id already exist.");
				break;
			}
		}

		if (!exist) {
			posts.push(id);
		}

		return !exist;
	}
	function _pop(id) {
		var indexOfId = posts.length;
		while (indexOfId--) {
			if (posts[indexOfId] === id) {
				posts = posts.slice(indexOfId);
				break;
			}
		}
	}
	return {
		push: _push,
		pop: _pop,
	};
};
var IdMaker = function() {
	var global_handle = 0;
	function _make() {
		return global_handle++;
	}
	return {
		make: _make,
	};
};
var Post = function(title, contents, option) {

	this.title = title;
	this.contents = contents;
	this.option = option;
	this.zIndex = 0;
	this.handle = IdMaker.make();

	PostManager.push(this.handle);
};
Post.prototype.activate = function() {
	var len = this.manager.length;
	for (var i = 0; i < len; i++) {
	}
};


