(function orderApp() {
	var IdCreator = (function () {
		var _global_id = 0;
		function _get() {
			return "id" + (_global_id++);
		}
		return {
			get: _get,
		};
	})();
	var PostManager = (function () {
		var board = null;
		function _init() {
			board = document.getElementById("board");
			if (board === null) {
				board = document.createElement("div");
				board.id = "board";
				document.body.appendChild(board);
			}
			console.log(board);
		}
		window.addEventListener("load", _init);
		function _add(contents) {
			console.log("PostManager::add");
			var item = document.createElement("div");
			item.id = IdCreator.get();
			item.className = "clickable";

			if (contents === undefined || contents.length === 0) {
				contents = "none";
			}

			var close = document.createElement("div");
			close.className = "button";
			close.innerHTML = "close";
			item.appendChild(close);

			function onClickClose(e) {
				var target = e.target.parentNode.id;
				_remove(target);
			}
			close.addEventListener("click", onClickClose);

			var totop = document.createElement("div");
			totop.className = "button";
			totop.innerHTML = "to top";
			item.appendChild(totop);

			function onClickToTop(e) {
				var target = e.target.parentNode.id;
				_totop(target);
			}
			totop.addEventListener("click", onClickToTop);

			var text = document.createTextNode(contents);
			item.appendChild(text);

			board.appendChild(item);
		}
		function _remove(id) {
			console.log("PostManager::remove");
			var target = document.getElementById(id);
			if (target === null) {
				console.log("[" + id + "] not found");
				return;
			}
			board.removeChild(target);
		}
		function _totop(id) {
			console.log("PostManager::totop");
			var target = document.getElementById(id);
			if (target === null) {
				console.log("[" + id + "] not found");
				return;
			}

			var count = board.childNodes.length;
			if (count < 1) {
				return;
			}
			else {
				board.removeChild(target);
				var first = board.firstChild;
				board.insertBefore(target, first);
			}
		}
		return {
			add: _add,
			remove: _remove,
		};
	})();
	function onWindowLoaded(e) {
		var action = document.getElementById("action");
		function onAddItemClick(e) {
			PostManager.add(action.name.value);
		}
		action.additem.addEventListener("click", onAddItemClick);
	}
	window.addEventListener("load", onWindowLoaded);
})();

