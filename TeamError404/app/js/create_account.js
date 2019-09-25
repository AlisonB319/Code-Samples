var Account = (function() {

    var apiUrl = 'https://teamerror404.herokuapp.com/';

    // var apiUrl = 'https://smile451.herokuapp.com';
    var userAccount;
    /**
     * HTTP GET request 
     * @param  {string}   url       URL path, e.g. "/api/smiles"
     * @param  {function} onSuccess   callback method to execute upon request success (200 status)
     * @param  {function} onFailure   callback method to execute upon request failure (non-200 status)
     * @return {None}
     */

    var makeGetRequest = function(url, onSuccess, onFailure) {
        $.ajax({
            type: 'GET',
            url: apiUrl + url,
            dataType: "json",
            success: onSuccess,
            error: onFailure
        });
    };
    
    /**
     * HTTP POST request
     * @param  {string}   url       URL path, e.g. "/api/smiles"
     * @param  {Object}   data      JSON data to send in request body
     * @param  {function} onSuccess   callback method to execute upon request success (200 status)
     * @param  {function} onFailure   callback method to execute upon request failure (non-200 status)
     * @return {None}
     */
    var makePostRequest = function(url, data, onSuccess, onFailure) {
        $.ajax({
            type: 'POST',
            url: apiUrl + url,
            data: JSON.stringify(data),
            contentType: "application/json",
            dataType: "json",
            success: onSuccess,
            error: onFailure
        });
    };

    var createAccountHandler = function (email, pword, type, onSuccess, onFailure) {
        userAccount.on("click", ".fac", function(e) {
            var newUser;
            newUser.firstName = userAccount.find(".fname").val();
            newUser.lastName = userAccount.find(".lname").val();
            newUser.email = userAccount.find(".wsuemail").val();
            newUser.password = userAccount.find(".psword").val();
            newUser.WSUID = userAccount.find(".wsuemail").val();
            newUser.phoneNumber = userAccount.find(".phnum").val();
            newUser.account_type = 'F';
        })
        userAccount.on("click", ".stu", function(e) {
            var newUser;
            newUser.firstName = userAccount.find(".fname").val();
            newUser.lastName = userAccount.find(".lname").val();
            newUser.email = userAccount.find(".wsuemail").val();
            newUser.password = userAccount.find(".psword").val();
            newUser.WSUID = userAccount.find(".wsuemail").val();
            newUser.phoneNumber = userAccount.find(".phnum").val();
            newUser.account_type = 'S';
        })

        var onSuccess = function(data) {
            if (data.status == -1) {
                console.error(data.errors);
                return;
            }
            // createAccount(newUser);

            userAccount.find(".fname").val('');
            userAccount.find(".lname").val('');
            userAccount.find(".wsuemail").val('');
            userAccount.find(".psword").val('');
            userAccount.find(".wsuemail").val('');
            userAccount.find(".phnum").val('');
        };
        var onFailure = function() {
            console.error("error creating account");
        };

        makePostRequest('api/createAccount', newUser, onSuccess, onFailure);
    }


    var start = function() {
        userAccount = $(".entry");
        createAccountHandler();

    }
});


