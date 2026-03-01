/// Package Modules
import * as Compiler from './_exports';

//  TOOL RUNNER  //

(async () => {
    // prepare the abort-controller to be used now
    const controller = new AbortController();

    // prepare the incoming targets to be handled
    const targets = Compiler.Target.native();

    // prepare the options to be used now
    const options = Compiler.Spawn({ stdio: true, abort: controller.signal });

    // and attempt executing each item one-by-one for testing
    for (const target of targets) {
        const worker = Compiler.Spawn.cmake(target, options);
        if (await worker.start()) process.exit(1); // failure
    }
})();
