/// Package Modules
import { Module } from './module';
import { Branch } from './product';
import { Context } from './context';
import { Plugins } from './plugins';

//  TOOL RUNNER  //

(async () => {
    // allow deciding a suitable release candidate
    const branch = process.argv.at(2);

    // ensure the incoming branch is valid now
    if (!Branch.validate(branch)) process.exit();

    // construct the container and options to use
    const options: Context.Options = { branch };

    // construct the container and then launch as expected
    const container = await Module.preload(options);
    await container.get(Context).launch(...Plugins());
})();
